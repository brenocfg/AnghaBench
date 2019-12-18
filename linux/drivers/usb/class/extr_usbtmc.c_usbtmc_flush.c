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
struct usbtmc_file_data {int /*<<< orphan*/  err_lock; scalar_t__ out_transfer_size; scalar_t__ out_status; scalar_t__ in_urbs_used; scalar_t__ in_transfer_size; scalar_t__ in_status; struct usbtmc_device_data* data; int /*<<< orphan*/  closing; } ;
struct usbtmc_device_data {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  waitq; } ;
struct file {struct usbtmc_file_data* private_data; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbtmc_draw_down (struct usbtmc_file_data*) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbtmc_flush(struct file *file, fl_owner_t id)
{
	struct usbtmc_file_data *file_data;
	struct usbtmc_device_data *data;

	file_data = file->private_data;
	if (file_data == NULL)
		return -ENODEV;

	atomic_set(&file_data->closing, 1);
	data = file_data->data;

	/* wait for io to stop */
	mutex_lock(&data->io_mutex);

	usbtmc_draw_down(file_data);

	spin_lock_irq(&file_data->err_lock);
	file_data->in_status = 0;
	file_data->in_transfer_size = 0;
	file_data->in_urbs_used = 0;
	file_data->out_status = 0;
	file_data->out_transfer_size = 0;
	spin_unlock_irq(&file_data->err_lock);

	wake_up_interruptible_all(&data->waitq);
	mutex_unlock(&data->io_mutex);

	return 0;
}