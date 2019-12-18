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
struct w1_slave {TYPE_1__* master; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 size_t EIO ; 
 int /*<<< orphan*/  W1_F0D_EEPROM_SIZE ; 
 int W1_F0D_READ_MAXLEN ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t w1_f0d_fix_count (int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ w1_f0d_readblock (struct w1_slave*,int,int,char*) ; 

__attribute__((used)) static ssize_t w1_f0d_read_bin(struct file *filp, struct kobject *kobj,
			       struct bin_attribute *bin_attr,
			       char *buf, loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int todo = count;

	count = w1_f0d_fix_count(off, count, W1_F0D_EEPROM_SIZE);
	if (count == 0)
		return 0;

	mutex_lock(&sl->master->mutex);

	/* read directly from the EEPROM in chunks of W1_F0D_READ_MAXLEN */
	while (todo > 0) {
		int block_read;

		if (todo >= W1_F0D_READ_MAXLEN)
			block_read = W1_F0D_READ_MAXLEN;
		else
			block_read = todo;

		if (w1_f0d_readblock(sl, off, block_read, buf) < 0) {
			count = -EIO;
			break;
		}

		todo -= W1_F0D_READ_MAXLEN;
		buf += W1_F0D_READ_MAXLEN;
		off += W1_F0D_READ_MAXLEN;
	}

	mutex_unlock(&sl->master->mutex);

	return count;
}