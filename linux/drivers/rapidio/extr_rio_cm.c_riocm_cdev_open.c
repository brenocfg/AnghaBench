#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  cm_dev_list ; 
 TYPE_1__* current ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 

__attribute__((used)) static int riocm_cdev_open(struct inode *inode, struct file *filp)
{
	riocm_debug(INIT, "by %s(%d) filp=%p ",
		    current->comm, task_pid_nr(current), filp);

	if (list_empty(&cm_dev_list))
		return -ENODEV;

	return 0;
}