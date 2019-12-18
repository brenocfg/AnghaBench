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
struct w83793_data {int /*<<< orphan*/  kref; int /*<<< orphan*/  watchdog_is_open; TYPE_1__* client; scalar_t__ watchdog_expect_close; } ;
struct inode {int dummy; } ;
struct file {struct w83793_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w83793_release_resources ; 
 int /*<<< orphan*/  watchdog_data_mutex ; 
 int /*<<< orphan*/  watchdog_disable (struct w83793_data*) ; 
 int /*<<< orphan*/  watchdog_trigger (struct w83793_data*) ; 

__attribute__((used)) static int watchdog_close(struct inode *inode, struct file *filp)
{
	struct w83793_data *data = filp->private_data;

	if (data->watchdog_expect_close) {
		watchdog_disable(data);
		data->watchdog_expect_close = 0;
	} else {
		watchdog_trigger(data);
		dev_crit(&data->client->dev,
			"unexpected close, not stopping watchdog!\n");
	}

	clear_bit(0, &data->watchdog_is_open);

	/* Decrease data reference counter */
	mutex_lock(&watchdog_data_mutex);
	kref_put(&data->kref, w83793_release_resources);
	mutex_unlock(&watchdog_data_mutex);

	return 0;
}