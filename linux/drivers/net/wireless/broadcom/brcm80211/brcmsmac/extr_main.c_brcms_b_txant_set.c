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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {int /*<<< orphan*/  up; int /*<<< orphan*/  bmac_phytxant; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_ucode_txant_set (struct brcms_hardware*) ; 

void brcms_b_txant_set(struct brcms_hardware *wlc_hw, u16 phytxant)
{
	/* update sw state */
	wlc_hw->bmac_phytxant = phytxant;

	/* push to ucode if up */
	if (!wlc_hw->up)
		return;
	brcms_c_ucode_txant_set(wlc_hw);

}