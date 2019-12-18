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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct dentry* smsdvb_debugfs_usb_root ; 
 int /*<<< orphan*/  usb_debug_root ; 

void smsdvb_debugfs_register(void)
{
	struct dentry *d;

	/*
	 * FIXME: This was written to debug Siano USB devices. So, it creates
	 * the debugfs node under <debugfs>/usb.
	 * A similar logic would be needed for Siano sdio devices, but, in that
	 * case, usb_debug_root is not a good choice.
	 *
	 * Perhaps the right fix here would be to create another sysfs root
	 * node for sdio-based boards, but this may need some logic at sdio
	 * subsystem.
	 */
	d = debugfs_create_dir("smsdvb", usb_debug_root);
	if (IS_ERR_OR_NULL(d)) {
		pr_err("Couldn't create sysfs node for smsdvb\n");
		return;
	}
	smsdvb_debugfs_usb_root = d;
}