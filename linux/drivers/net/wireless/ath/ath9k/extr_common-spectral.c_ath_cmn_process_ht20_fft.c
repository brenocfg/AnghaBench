#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u16 ;
struct fft_sample_tlv {int dummy; } ;
struct TYPE_2__ {void* length; int /*<<< orphan*/  type; } ;
struct fft_sample_ht20 {size_t max_index; size_t bitmap_weight; size_t max_exp; int* data; void* max_magnitude; int /*<<< orphan*/  tsf; int /*<<< orphan*/  noise; int /*<<< orphan*/  rssi; void* freq; TYPE_1__ tlv; } ;
struct ath_spec_scan_priv {struct ath_hw* ah; } ;
struct ath_rx_status {int /*<<< orphan*/ * rs_rssi_ctl; } ;
struct ath_hw {int /*<<< orphan*/  noise; } ;
struct ath_ht20_mag_info {int max_exp; int /*<<< orphan*/  all_bins; } ;
struct ath_common {int dummy; } ;
typedef  int /*<<< orphan*/  fft_sample_20 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_FFT_SAMPLE_HT20 ; 
 int SPECTRAL_HT20_NUM_BINS ; 
 int /*<<< orphan*/  SPECTRAL_SCAN ; 
 void* __cpu_to_be16 (size_t) ; 
 int /*<<< orphan*/  __cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_debug_send_fft_sample (struct ath_spec_scan_priv*,struct fft_sample_tlv*) ; 
 int /*<<< orphan*/  fix_rssi_inv_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,size_t*,int) ; 
 size_t spectral_bitmap_weight (int /*<<< orphan*/ ) ; 
 size_t spectral_max_index_ht20 (int /*<<< orphan*/ ) ; 
 size_t spectral_max_magnitude (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath_cmn_process_ht20_fft(struct ath_rx_status *rs,
			struct ath_spec_scan_priv *spec_priv,
			u8 *sample_buf,
			u64 tsf, u16 freq, int chan_type)
{
	struct fft_sample_ht20 fft_sample_20;
	struct ath_common *common = ath9k_hw_common(spec_priv->ah);
	struct ath_hw *ah = spec_priv->ah;
	struct ath_ht20_mag_info *mag_info;
	struct fft_sample_tlv *tlv;
	int i = 0;
	int ret = 0;
	int dc_pos = SPECTRAL_HT20_NUM_BINS / 2;
	u16 magnitude, tmp_mag, length;
	u8 max_index, bitmap_w, max_exp;

	length = sizeof(fft_sample_20) - sizeof(struct fft_sample_tlv);
	fft_sample_20.tlv.type = ATH_FFT_SAMPLE_HT20;
	fft_sample_20.tlv.length = __cpu_to_be16(length);
	fft_sample_20.freq = __cpu_to_be16(freq);
	fft_sample_20.rssi = fix_rssi_inv_only(rs->rs_rssi_ctl[0]);
	fft_sample_20.noise = ah->noise;

	mag_info = (struct ath_ht20_mag_info *) (sample_buf +
					SPECTRAL_HT20_NUM_BINS);

	magnitude = spectral_max_magnitude(mag_info->all_bins);
	fft_sample_20.max_magnitude = __cpu_to_be16(magnitude);

	max_index = spectral_max_index_ht20(mag_info->all_bins);
	fft_sample_20.max_index = max_index;

	bitmap_w = spectral_bitmap_weight(mag_info->all_bins);
	fft_sample_20.bitmap_weight = bitmap_w;

	max_exp = mag_info->max_exp & 0xf;
	fft_sample_20.max_exp = max_exp;

	fft_sample_20.tsf = __cpu_to_be64(tsf);

	memcpy(fft_sample_20.data, sample_buf, SPECTRAL_HT20_NUM_BINS);

	ath_dbg(common, SPECTRAL_SCAN, "FFT HT20 frame: max mag 0x%X,"
					"max_mag_idx %i\n",
					magnitude >> max_exp,
					max_index);

	if ((fft_sample_20.data[max_index] & 0xf8) !=
	    ((magnitude >> max_exp) & 0xf8)) {
		ath_dbg(common, SPECTRAL_SCAN, "Magnitude mismatch !\n");
		ret = -1;
	}

	/* DC value (value in the middle) is the blind spot of the spectral
	 * sample and invalid, interpolate it.
	 */
	fft_sample_20.data[dc_pos] = (fft_sample_20.data[dc_pos + 1] +
					fft_sample_20.data[dc_pos - 1]) / 2;

	/* Check if the maximum magnitude is indeed maximum,
	 * also if the maximum value was at dc_pos, calculate
	 * a new one (since value at dc_pos is invalid).
	 */
	if (max_index == dc_pos) {
		tmp_mag = 0;
		for (i = 0; i < dc_pos; i++) {
			if (fft_sample_20.data[i] > tmp_mag) {
				tmp_mag = fft_sample_20.data[i];
				fft_sample_20.max_index = i;
			}
		}

		magnitude = tmp_mag << max_exp;
		fft_sample_20.max_magnitude = __cpu_to_be16(magnitude);

		ath_dbg(common, SPECTRAL_SCAN,
			"Calculated new lower max 0x%X at %i\n",
			tmp_mag, fft_sample_20.max_index);
	} else
	for (i = 0; i < SPECTRAL_HT20_NUM_BINS; i++) {
		if (fft_sample_20.data[i] == (magnitude >> max_exp))
			ath_dbg(common, SPECTRAL_SCAN,
				"Got max: 0x%X at index %i\n",
				fft_sample_20.data[i], i);

		if (fft_sample_20.data[i] > (magnitude >> max_exp)) {
			ath_dbg(common, SPECTRAL_SCAN,
				"Got bin %i greater than max: 0x%X\n",
				i, fft_sample_20.data[i]);
			ret = -1;
		}
	}

	if (ret < 0)
		return ret;

	tlv = (struct fft_sample_tlv *)&fft_sample_20;

	ath_debug_send_fft_sample(spec_priv, tlv);

	return 0;
}