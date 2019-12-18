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
typedef  int /*<<< orphan*/  u8 ;
struct brcms_hardware {TYPE_1__* band; int /*<<< orphan*/  antsel_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_phy_antsel_type_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void brcms_b_antsel_type_set(struct brcms_hardware *wlc_hw, u8 antsel_type)
{
	wlc_hw->antsel_type = antsel_type;

	/* Update the antsel type for phy module to use */
	wlc_phy_antsel_type_set(wlc_hw->band->pi, antsel_type);
}