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
struct adv748x_csi2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV748X_CSI_FS_AS_LS ; 
 int ADV748X_CSI_FS_AS_LS_UNKNOWN ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int adv748x_power_down_tx (struct adv748x_csi2*) ; 
 int adv748x_power_up_tx (struct adv748x_csi2*) ; 
 int /*<<< orphan*/  is_tx_enabled (struct adv748x_csi2*) ; 
 int tx_read (struct adv748x_csi2*,int /*<<< orphan*/ ) ; 

int adv748x_tx_power(struct adv748x_csi2 *tx, bool on)
{
	int val;

	if (!is_tx_enabled(tx))
		return 0;

	val = tx_read(tx, ADV748X_CSI_FS_AS_LS);
	if (val < 0)
		return val;

	/*
	 * This test against BIT(6) is not documented by the datasheet, but was
	 * specified in the downstream driver.
	 * Track with a WARN_ONCE to determine if it is ever set by HW.
	 */
	WARN_ONCE((on && val & ADV748X_CSI_FS_AS_LS_UNKNOWN),
			"Enabling with unknown bit set");

	return on ? adv748x_power_up_tx(tx) : adv748x_power_down_tx(tx);
}