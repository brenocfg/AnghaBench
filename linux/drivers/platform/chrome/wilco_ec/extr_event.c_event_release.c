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
struct file {struct event_device_data* private_data; } ;
struct event_device_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  available; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int event_release(struct inode *inode, struct file *filp)
{
	struct event_device_data *dev_data = filp->private_data;

	atomic_set(&dev_data->available, 1);
	put_device(&dev_data->dev);

	return 0;
}