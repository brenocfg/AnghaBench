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
struct pi433_instance {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct pi433_instance* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pi433_instance*) ; 

__attribute__((used)) static int pi433_release(struct inode *inode, struct file *filp)
{
	struct pi433_instance	*instance;

	instance = filp->private_data;
	kfree(instance);
	filp->private_data = NULL;

	return 0;
}