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
struct media_devnode {TYPE_1__* fops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioctl; } ;

/* Variables and functions */
 long __media_ioctl (struct file*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 
 struct media_devnode* media_devnode_data (struct file*) ; 

__attribute__((used)) static long media_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct media_devnode *devnode = media_devnode_data(filp);

	return __media_ioctl(filp, cmd, arg, devnode->fops->ioctl);
}