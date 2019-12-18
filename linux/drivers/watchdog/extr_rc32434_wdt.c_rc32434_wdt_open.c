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
struct TYPE_2__ {int /*<<< orphan*/  inuse; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ nowayout ; 
 TYPE_1__ rc32434_wdt_device ; 
 int /*<<< orphan*/  rc32434_wdt_ping () ; 
 int /*<<< orphan*/  rc32434_wdt_start () ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rc32434_wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &rc32434_wdt_device.inuse))
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	rc32434_wdt_start();
	rc32434_wdt_ping();

	return stream_open(inode, file);
}