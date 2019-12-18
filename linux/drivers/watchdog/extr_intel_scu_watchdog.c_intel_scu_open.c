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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ driver_closed; int /*<<< orphan*/  driver_open; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ watchdog_device ; 

__attribute__((used)) static int intel_scu_open(struct inode *inode, struct file *file)
{

	/* Set flag to indicate that watchdog device is open */
	if (test_and_set_bit(0, &watchdog_device.driver_open))
		return -EBUSY;

	/* Check for reopen of driver. Reopens are not allowed */
	if (watchdog_device.driver_closed)
		return -EPERM;

	return stream_open(inode, file);
}