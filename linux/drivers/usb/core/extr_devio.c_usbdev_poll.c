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
struct usb_dev_state {int /*<<< orphan*/  list; int /*<<< orphan*/  async_completed; int /*<<< orphan*/  wait; } ;
struct poll_table_struct {int dummy; } ;
struct file {int f_mode; struct usb_dev_state* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLOUT ; 
 int EPOLLWRNORM ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  connected (struct usb_dev_state*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t usbdev_poll(struct file *file,
				struct poll_table_struct *wait)
{
	struct usb_dev_state *ps = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &ps->wait, wait);
	if (file->f_mode & FMODE_WRITE && !list_empty(&ps->async_completed))
		mask |= EPOLLOUT | EPOLLWRNORM;
	if (!connected(ps))
		mask |= EPOLLHUP;
	if (list_empty(&ps->list))
		mask |= EPOLLERR;
	return mask;
}