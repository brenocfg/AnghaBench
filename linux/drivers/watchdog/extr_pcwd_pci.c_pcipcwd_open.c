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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ VERBOSE ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  is_active ; 
 int /*<<< orphan*/  pcipcwd_keepalive () ; 
 int /*<<< orphan*/  pcipcwd_start () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcipcwd_open(struct inode *inode, struct file *file)
{
	/* /dev/watchdog can only be opened once */
	if (test_and_set_bit(0, &is_active)) {
		if (debug >= VERBOSE)
			pr_err("Attempt to open already opened device\n");
		return -EBUSY;
	}

	/* Activate */
	pcipcwd_start();
	pcipcwd_keepalive();
	return stream_open(inode, file);
}