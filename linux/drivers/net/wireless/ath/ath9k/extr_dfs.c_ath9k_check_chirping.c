#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath_hw {int /*<<< orphan*/  curchan; } ;
struct ath_common {int dummy; } ;
struct ath9k_dfs_fft_40 {int dummy; } ;
struct ath9k_dfs_fft_20 {int /*<<< orphan*/  lower_bins; } ;

/* Variables and functions */
 scalar_t__ BIN_DELTA_MAX ; 
 scalar_t__ BIN_DELTA_MIN ; 
 int /*<<< orphan*/  DFS ; 
 int FFT_NUM_SAMPLES ; 
 scalar_t__ IS_CHAN_HT40 (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHAN_HT40MINUS (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_DIFF ; 
 int NUM_DIFFS ; 
 scalar_t__ abs (int) ; 
 int ath9k_get_max_index_ht40 (struct ath9k_dfs_fft_40*,int,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int fft_max_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static bool ath9k_check_chirping(struct ath_softc *sc, u8 *data,
				 int datalen, bool is_ctl, bool is_ext)
{
	int i;
	int max_bin[FFT_NUM_SAMPLES];
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	int prev_delta;

	if (IS_CHAN_HT40(ah->curchan)) {
		struct ath9k_dfs_fft_40 *fft = (struct ath9k_dfs_fft_40 *) data;
		int num_fft_packets = datalen / sizeof(*fft);
		if (num_fft_packets == 0)
			return false;

		ath_dbg(common, DFS, "HT40: datalen=%d, num_fft_packets=%d\n",
			datalen, num_fft_packets);
		if (num_fft_packets < FFT_NUM_SAMPLES) {
			ath_dbg(common, DFS, "not enough packets for chirp\n");
			return false;
		}
		/* HW sometimes adds 2 garbage bytes in front of FFT samples */
		if ((datalen % sizeof(*fft)) == 2) {
			fft = (struct ath9k_dfs_fft_40 *) (data + 2);
			ath_dbg(common, DFS, "fixing datalen by 2\n");
		}
		if (IS_CHAN_HT40MINUS(ah->curchan))
			swap(is_ctl, is_ext);

		for (i = 0; i < FFT_NUM_SAMPLES; i++)
			max_bin[i] = ath9k_get_max_index_ht40(fft + i, is_ctl,
							      is_ext);
	} else {
		struct ath9k_dfs_fft_20 *fft = (struct ath9k_dfs_fft_20 *) data;
		int num_fft_packets = datalen / sizeof(*fft);
		if (num_fft_packets == 0)
			return false;
		ath_dbg(common, DFS, "HT20: datalen=%d, num_fft_packets=%d\n",
			datalen, num_fft_packets);
		if (num_fft_packets < FFT_NUM_SAMPLES) {
			ath_dbg(common, DFS, "not enough packets for chirp\n");
			return false;
		}
		/* in ht20, this is a 6-bit signed number => shift it to 0 */
		for (i = 0; i < FFT_NUM_SAMPLES; i++)
			max_bin[i] = fft_max_index(fft[i].lower_bins) ^ 0x20;
	}
	ath_dbg(common, DFS, "bin_max = [%d, %d, %d, %d]\n",
		max_bin[0], max_bin[1], max_bin[2], max_bin[3]);

	/* Check for chirp attributes within specs
	 * a) delta of adjacent max_bins is within range
	 * b) delta of adjacent deltas are within tolerance
	 */
	prev_delta = 0;
	for (i = 0; i < NUM_DIFFS; i++) {
		int ddelta = -1;
		int delta = max_bin[i + 1] - max_bin[i];

		/* ensure gradient is within valid range */
		if (abs(delta) < BIN_DELTA_MIN || abs(delta) > BIN_DELTA_MAX) {
			ath_dbg(common, DFS, "CHIRP: invalid delta %d "
				"in sample %d\n", delta, i);
			return false;
		}
		if (i == 0)
			goto done;
		ddelta = delta - prev_delta;
		if (abs(ddelta) > MAX_DIFF) {
			ath_dbg(common, DFS, "CHIRP: ddelta %d too high\n",
				ddelta);
			return false;
		}
done:
		ath_dbg(common, DFS, "CHIRP - %d: delta=%d, ddelta=%d\n",
			i, delta, ddelta);
		prev_delta = delta;
	}
	return true;
}