#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct w1_slave {int /*<<< orphan*/  dev; TYPE_2__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct bin_attribute {TYPE_1__ attr; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  W1_F3A_FUNC_PIO_ACCESS_READ ; 
 int W1_F3A_INVALID_PIO_STATE ; 
 unsigned int W1_F3A_RETRIES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w1_read_8 (TYPE_2__*) ; 
 scalar_t__ w1_reset_resume_command (TYPE_2__*) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_8 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t state_read(struct file *filp, struct kobject *kobj,
			  struct bin_attribute *bin_attr, char *buf, loff_t off,
			  size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	unsigned int retries = W1_F3A_RETRIES;
	ssize_t bytes_read = -EIO;
	u8 state;

	dev_dbg(&sl->dev,
		"Reading %s kobj: %p, off: %0#10x, count: %zu, buff addr: %p",
		bin_attr->attr.name, kobj, (unsigned int)off, count, buf);

	if (off != 0)
		return 0;
	if (!buf)
		return -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "mutex locked");

next:
	if (w1_reset_select_slave(sl))
		goto out;

	while (retries--) {
		w1_write_8(sl->master, W1_F3A_FUNC_PIO_ACCESS_READ);

		state = w1_read_8(sl->master);
		if ((state & 0x0F) == ((~state >> 4) & 0x0F)) {
			/* complement is correct */
			*buf = state;
			bytes_read = 1;
			goto out;
		} else if (state == W1_F3A_INVALID_PIO_STATE) {
			/* slave didn't respond, try to select it again */
			dev_warn(&sl->dev, "slave device did not respond to PIO_ACCESS_READ, " \
					    "reselecting, retries left: %d\n", retries);
			goto next;
		}

		if (w1_reset_resume_command(sl->master))
			goto out; /* unrecoverable error */

		dev_warn(&sl->dev, "PIO_ACCESS_READ error, retries left: %d\n", retries);
	}

out:
	mutex_unlock(&sl->master->bus_mutex);
	dev_dbg(&sl->dev, "%s, mutex unlocked, retries: %d\n",
		(bytes_read > 0) ? "succeeded" : "error", retries);
	return bytes_read;
}