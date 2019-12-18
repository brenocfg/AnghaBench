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
struct mwifiex_private {struct mwifiex_histogram_data* hist_data; } ;
struct mwifiex_histogram_data {int /*<<< orphan*/ * sig_str; int /*<<< orphan*/ * noise_flr; int /*<<< orphan*/ * snr; int /*<<< orphan*/ * rx_rate; int /*<<< orphan*/  num_samples; } ;

/* Variables and functions */
 int MWIFIEX_MAX_AC_RX_RATES ; 
 int MWIFIEX_MAX_NOISE_FLR ; 
 int MWIFIEX_MAX_SIG_STRENGTH ; 
 int MWIFIEX_MAX_SNR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mwifiex_hist_data_reset(struct mwifiex_private *priv)
{
	int ix;
	struct mwifiex_histogram_data *phist_data = priv->hist_data;

	atomic_set(&phist_data->num_samples, 0);
	for (ix = 0; ix < MWIFIEX_MAX_AC_RX_RATES; ix++)
		atomic_set(&phist_data->rx_rate[ix], 0);
	for (ix = 0; ix < MWIFIEX_MAX_SNR; ix++)
		atomic_set(&phist_data->snr[ix], 0);
	for (ix = 0; ix < MWIFIEX_MAX_NOISE_FLR; ix++)
		atomic_set(&phist_data->noise_flr[ix], 0);
	for (ix = 0; ix < MWIFIEX_MAX_SIG_STRENGTH; ix++)
		atomic_set(&phist_data->sig_str[ix], 0);
}