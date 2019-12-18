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
struct brcms_hardware {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_ISNPHY (int /*<<< orphan*/ ) ; 
 int ON ; 
 int /*<<< orphan*/  SICF_FGC ; 
 int /*<<< orphan*/  brcms_b_core_ioctl (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void brcms_b_phyclk_fgc(struct brcms_hardware *wlc_hw, bool clk)
{
	/* support(necessary for NPHY and HYPHY) only */
	if (!BRCMS_ISNPHY(wlc_hw->band))
		return;

	if (ON == clk)
		brcms_b_core_ioctl(wlc_hw, SICF_FGC, SICF_FGC);
	else
		brcms_b_core_ioctl(wlc_hw, SICF_FGC, 0);

}