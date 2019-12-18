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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 scalar_t__ b43_nphy_gen_load_samples (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  b43_nphy_run_samples (struct b43_wldev*,scalar_t__,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int b43_nphy_tx_tone(struct b43_wldev *dev, u32 freq, u16 max_val,
			    bool iqmode, bool dac_test, bool modify_bbmult)
{
	u16 samp = b43_nphy_gen_load_samples(dev, freq, max_val, dac_test);
	if (samp == 0)
		return -1;
	b43_nphy_run_samples(dev, samp, 0xFFFF, 0, iqmode, dac_test,
			     modify_bbmult);
	return 0;
}