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
struct adv748x_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CSI_FS_AS_LS ; 
 int ADV748X_CSI_FS_AS_LS_UNKNOWN ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  adv748x_power_down_txb_1lane ; 
 int /*<<< orphan*/  adv748x_power_up_txb_1lane ; 
 int adv748x_write_regs (struct adv748x_state*,int /*<<< orphan*/ ) ; 
 int txb_read (struct adv748x_state*,int /*<<< orphan*/ ) ; 

int adv748x_txb_power(struct adv748x_state *state, bool on)
{
	int val;

	val = txb_read(state, ADV748X_CSI_FS_AS_LS);
	if (val < 0)
		return val;

	/*
	 * This test against BIT(6) is not documented by the datasheet, but was
	 * specified in the downstream driver.
	 * Track with a WARN_ONCE to determine if it is ever set by HW.
	 */
	WARN_ONCE((on && val & ADV748X_CSI_FS_AS_LS_UNKNOWN),
			"Enabling with unknown bit set");

	if (on)
		return adv748x_write_regs(state, adv748x_power_up_txb_1lane);

	return adv748x_write_regs(state, adv748x_power_down_txb_1lane);
}