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
struct au0828_dev {int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  DEV_MISCONFIGURED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_dev(struct au0828_dev *dev)
{
	if (test_bit(DEV_DISCONNECTED, &dev->dev_state)) {
		pr_info("v4l2 ioctl: device not present\n");
		return -ENODEV;
	}

	if (test_bit(DEV_MISCONFIGURED, &dev->dev_state)) {
		pr_info("v4l2 ioctl: device is misconfigured; close and open it again\n");
		return -EIO;
	}
	return 0;
}