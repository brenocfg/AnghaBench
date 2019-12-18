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
struct i1480 {int /*<<< orphan*/  (* rc_release ) (struct i1480*) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  mac_fw_name; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int i1480_mac_fw_upload (struct i1480*) ; 
 int i1480_phy_fw_upload (struct i1480*) ; 
 int i1480_pre_fw_upload (struct i1480*) ; 
 int /*<<< orphan*/  i1480_print_state (struct i1480*) ; 
 int /*<<< orphan*/  stub1 (struct i1480*) ; 

int i1480_fw_upload(struct i1480 *i1480)
{
	int result;

	result = i1480_pre_fw_upload(i1480);	/* PHY pre fw */
	if (result < 0 && result != -ENOENT) {
		i1480_print_state(i1480);
		goto error;
	}
	result = i1480_mac_fw_upload(i1480);	/* MAC fw */
	if (result < 0) {
		if (result == -ENOENT)
			dev_err(i1480->dev, "Cannot locate MAC FW file '%s'\n",
				i1480->mac_fw_name);
		else
			i1480_print_state(i1480);
		goto error;
	}
	result = i1480_phy_fw_upload(i1480);	/* PHY fw */
	if (result < 0 && result != -ENOENT) {
		i1480_print_state(i1480);
		goto error_rc_release;
	}
	/*
	 * FIXME: find some reliable way to check whether firmware is running
	 * properly. Maybe use some standard request that has no side effects?
	 */
	dev_info(i1480->dev, "firmware uploaded successfully\n");
error_rc_release:
	if (i1480->rc_release)
		i1480->rc_release(i1480);
	result = 0;
error:
	return result;
}