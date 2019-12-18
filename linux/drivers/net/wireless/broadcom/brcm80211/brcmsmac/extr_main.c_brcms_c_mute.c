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
struct brcms_c_info {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_b_mute (int /*<<< orphan*/ ,int) ; 

void
brcms_c_mute(struct brcms_c_info *wlc, bool mute_tx)
{
	brcms_b_mute(wlc->hw, mute_tx);
}