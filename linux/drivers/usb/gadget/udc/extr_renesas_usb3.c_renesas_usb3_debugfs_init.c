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
struct renesas_usb3 {int /*<<< orphan*/  dentry; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct renesas_usb3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  renesas_usb3_b_device_fops ; 

__attribute__((used)) static void renesas_usb3_debugfs_init(struct renesas_usb3 *usb3,
				      struct device *dev)
{
	usb3->dentry = debugfs_create_dir(dev_name(dev), NULL);

	debugfs_create_file("b_device", 0644, usb3->dentry, usb3,
			    &renesas_usb3_b_device_fops);
}