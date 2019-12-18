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
struct usbtmc_file_data {int /*<<< orphan*/  err_lock; scalar_t__ out_status; scalar_t__ in_status; int /*<<< orphan*/  in_anchor; int /*<<< orphan*/  submitted; int /*<<< orphan*/  srq_asserted; struct usbtmc_device_data* data; } ;
struct usbtmc_device_data {int /*<<< orphan*/  io_mutex; TYPE_1__* intf; int /*<<< orphan*/  waitq; scalar_t__ zombie; } ;
struct file {struct usbtmc_file_data* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_anchor_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t usbtmc_poll(struct file *file, poll_table *wait)
{
	struct usbtmc_file_data *file_data = file->private_data;
	struct usbtmc_device_data *data = file_data->data;
	__poll_t mask;

	mutex_lock(&data->io_mutex);

	if (data->zombie) {
		mask = EPOLLHUP | EPOLLERR;
		goto no_poll;
	}

	poll_wait(file, &data->waitq, wait);

	/* Note that EPOLLPRI is now assigned to SRQ, and
	 * EPOLLIN|EPOLLRDNORM to normal read data.
	 */
	mask = 0;
	if (atomic_read(&file_data->srq_asserted))
		mask |= EPOLLPRI;

	/* Note that the anchor submitted includes all urbs for BULK IN
	 * and OUT. So EPOLLOUT is signaled when BULK OUT is empty and
	 * all BULK IN urbs are completed and moved to in_anchor.
	 */
	if (usb_anchor_empty(&file_data->submitted))
		mask |= (EPOLLOUT | EPOLLWRNORM);
	if (!usb_anchor_empty(&file_data->in_anchor))
		mask |= (EPOLLIN | EPOLLRDNORM);

	spin_lock_irq(&file_data->err_lock);
	if (file_data->in_status || file_data->out_status)
		mask |= EPOLLERR;
	spin_unlock_irq(&file_data->err_lock);

	dev_dbg(&data->intf->dev, "poll mask = %x\n", mask);

no_poll:
	mutex_unlock(&data->io_mutex);
	return mask;
}