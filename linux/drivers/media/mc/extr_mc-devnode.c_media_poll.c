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
struct poll_table_struct {int dummy; } ;
struct media_devnode {TYPE_1__* fops; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;
struct TYPE_2__ {int (* poll ) (struct file*,struct poll_table_struct*) ;} ;

/* Variables and functions */
 int DEFAULT_POLLMASK ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 struct media_devnode* media_devnode_data (struct file*) ; 
 int /*<<< orphan*/  media_devnode_is_registered (struct media_devnode*) ; 
 int stub1 (struct file*,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t media_poll(struct file *filp,
			       struct poll_table_struct *poll)
{
	struct media_devnode *devnode = media_devnode_data(filp);

	if (!media_devnode_is_registered(devnode))
		return EPOLLERR | EPOLLHUP;
	if (!devnode->fops->poll)
		return DEFAULT_POLLMASK;
	return devnode->fops->poll(filp, poll);
}