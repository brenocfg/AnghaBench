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
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * smsdvb_debugfs_usb_root ; 

void smsdvb_debugfs_unregister(void)
{
	if (!smsdvb_debugfs_usb_root)
		return;
	debugfs_remove_recursive(smsdvb_debugfs_usb_root);
	smsdvb_debugfs_usb_root = NULL;
}