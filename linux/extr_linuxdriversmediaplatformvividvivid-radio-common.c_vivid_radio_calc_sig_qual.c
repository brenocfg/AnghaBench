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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct vivid_dev {int radio_rx_freq; int radio_tx_freq; int radio_rds_loop; int radio_rx_sig_qual; TYPE_1__ rds_gen; int /*<<< orphan*/  radio_tx_rds_controls; scalar_t__ has_radio_tx; } ;

/* Variables and functions */
 int AM_FREQ_RANGE_HIGH ; 
 int FM_FREQ_RANGE_LOW ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vivid_radio_calc_sig_qual(struct vivid_dev *dev)
{
	int mod = 16000;
	int delta = 800;
	int sig_qual, sig_qual_tx = mod;

	/*
	 * For SW and FM there is a channel every 1000 kHz, for AM there is one
	 * every 100 kHz.
	 */
	if (dev->radio_rx_freq <= AM_FREQ_RANGE_HIGH) {
		mod /= 10;
		delta /= 10;
	}
	sig_qual = (dev->radio_rx_freq + delta) % mod - delta;
	if (dev->has_radio_tx)
		sig_qual_tx = dev->radio_rx_freq - dev->radio_tx_freq;
	if (abs(sig_qual_tx) <= abs(sig_qual)) {
		sig_qual = sig_qual_tx;
		/*
		 * Zero the internal rds buffer if we are going to loop
		 * rds blocks.
		 */
		if (!dev->radio_rds_loop && !dev->radio_tx_rds_controls)
			memset(dev->rds_gen.data, 0,
			       sizeof(dev->rds_gen.data));
		dev->radio_rds_loop = dev->radio_rx_freq >= FM_FREQ_RANGE_LOW;
	} else {
		dev->radio_rds_loop = false;
	}
	if (dev->radio_rx_freq <= AM_FREQ_RANGE_HIGH)
		sig_qual *= 10;
	dev->radio_rx_sig_qual = sig_qual;
}