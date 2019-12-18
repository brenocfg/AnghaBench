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
struct ath9k_dfs_fft_40 {int /*<<< orphan*/  upper_bins; int /*<<< orphan*/  lower_bins; } ;

/* Variables and functions */
 scalar_t__ fft_bitmap_weight (int /*<<< orphan*/ ) ; 
 int fft_max_index (int /*<<< orphan*/ ) ; 
 int fft_max_magnitude (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_get_max_index_ht40(struct ath9k_dfs_fft_40 *fft,
				    bool is_ctl, bool is_ext)
{
	const int DFS_UPPER_BIN_OFFSET = 64;
	/* if detected radar on both channels, select the significant one */
	if (is_ctl && is_ext) {
		/* first check wether channels have 'strong' bins */
		is_ctl = fft_bitmap_weight(fft->lower_bins) != 0;
		is_ext = fft_bitmap_weight(fft->upper_bins) != 0;

		/* if still unclear, take higher magnitude */
		if (is_ctl && is_ext) {
			int mag_lower = fft_max_magnitude(fft->lower_bins);
			int mag_upper = fft_max_magnitude(fft->upper_bins);
			if (mag_upper > mag_lower)
				is_ctl = false;
			else
				is_ext = false;
		}
	}
	if (is_ctl)
		return fft_max_index(fft->lower_bins);
	return fft_max_index(fft->upper_bins) + DFS_UPPER_BIN_OFFSET;
}