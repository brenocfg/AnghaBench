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

/* Variables and functions */
 int DNV_NUM_CHANNELS ; 
 int ENODEV ; 
 scalar_t__ RD_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RD_REGP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_cr_dmap ; 
 int /*<<< orphan*/  d_cr_dmap1 ; 
 int /*<<< orphan*/  d_cr_dmap2 ; 
 int /*<<< orphan*/  d_cr_dmap3 ; 
 int /*<<< orphan*/  d_cr_dmap4 ; 
 int /*<<< orphan*/  d_cr_dmap5 ; 
 int /*<<< orphan*/  d_cr_drp ; 
 int /*<<< orphan*/  d_cr_dsch ; 
 int /*<<< orphan*/  d_cr_ecc_ctrl ; 
 int /*<<< orphan*/ * dmap ; 
 int /*<<< orphan*/ * dmap1 ; 
 int /*<<< orphan*/ * dmap2 ; 
 int /*<<< orphan*/ * dmap3 ; 
 int /*<<< orphan*/ * dmap4 ; 
 int /*<<< orphan*/ * dmap5 ; 
 int /*<<< orphan*/ * dnv_dports ; 
 int /*<<< orphan*/ * drp ; 
 int /*<<< orphan*/  dsch ; 
 int /*<<< orphan*/ * ecc_ctrl ; 

__attribute__((used)) static int dnv_get_registers(void)
{
	int i;

	if (RD_REG(&dsch, d_cr_dsch))
		return -ENODEV;

	for (i = 0; i < DNV_NUM_CHANNELS; i++)
		if (RD_REGP(&ecc_ctrl[i], d_cr_ecc_ctrl, dnv_dports[i]) ||
			RD_REGP(&drp[i], d_cr_drp, dnv_dports[i]) ||
			RD_REGP(&dmap[i], d_cr_dmap, dnv_dports[i]) ||
			RD_REGP(&dmap1[i], d_cr_dmap1, dnv_dports[i]) ||
			RD_REGP(&dmap2[i], d_cr_dmap2, dnv_dports[i]) ||
			RD_REGP(&dmap3[i], d_cr_dmap3, dnv_dports[i]) ||
			RD_REGP(&dmap4[i], d_cr_dmap4, dnv_dports[i]) ||
			RD_REGP(&dmap5[i], d_cr_dmap5, dnv_dports[i]))
			return -ENODEV;

	return 0;
}