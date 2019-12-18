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
struct brcms_c_info {scalar_t__ shortslot_override; int shortslot; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ BRCMS_SHORTSLOT_AUTO ; 
 scalar_t__ BRCMS_SHORTSLOT_ON ; 
 int /*<<< orphan*/  brcms_b_set_shortslot (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcms_c_switch_shortslot(struct brcms_c_info *wlc, bool shortslot)
{
	/* use the override if it is set */
	if (wlc->shortslot_override != BRCMS_SHORTSLOT_AUTO)
		shortslot = (wlc->shortslot_override == BRCMS_SHORTSLOT_ON);

	if (wlc->shortslot == shortslot)
		return;

	wlc->shortslot = shortslot;

	brcms_b_set_shortslot(wlc->hw, shortslot);
}