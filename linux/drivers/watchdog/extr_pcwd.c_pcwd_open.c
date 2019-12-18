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
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  open_allowed ; 
 int /*<<< orphan*/  pcwd_keepalive () ; 
 int /*<<< orphan*/  pcwd_start () ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcwd_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &open_allowed))
		return -EBUSY;
	if (nowayout)
		__module_get(THIS_MODULE);
	/* Activate */
	pcwd_start();
	pcwd_keepalive();
	return stream_open(inode, file);
}