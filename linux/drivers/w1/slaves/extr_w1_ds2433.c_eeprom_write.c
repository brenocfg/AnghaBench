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
struct w1_slave {TYPE_1__* master; int /*<<< orphan*/  dev; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC16_INIT ; 
 scalar_t__ CRC16_VALID ; 
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  W1_EEPROM_SIZE ; 
 size_t W1_PAGE_MASK ; 
 int W1_PAGE_SIZE ; 
 scalar_t__ crc16 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t w1_f23_fix_count (size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ w1_f23_write (struct w1_slave*,int,int,char*) ; 

__attribute__((used)) static ssize_t eeprom_write(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr, char *buf,
			    loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
	int addr, len, idx;

	if ((count = w1_f23_fix_count(off, count, W1_EEPROM_SIZE)) == 0)
		return 0;

#ifdef CONFIG_W1_SLAVE_DS2433_CRC
	/* can only write full blocks in cached mode */
	if ((off & W1_PAGE_MASK) || (count & W1_PAGE_MASK)) {
		dev_err(&sl->dev, "invalid offset/count off=%d cnt=%zd\n",
			(int)off, count);
		return -EINVAL;
	}

	/* make sure the block CRCs are valid */
	for (idx = 0; idx < count; idx += W1_PAGE_SIZE) {
		if (crc16(CRC16_INIT, &buf[idx], W1_PAGE_SIZE) != CRC16_VALID) {
			dev_err(&sl->dev, "bad CRC at offset %d\n", (int)off);
			return -EINVAL;
		}
	}
#endif	/* CONFIG_W1_SLAVE_DS2433_CRC */

	mutex_lock(&sl->master->bus_mutex);

	/* Can only write data to one page at a time */
	idx = 0;
	while (idx < count) {
		addr = off + idx;
		len = W1_PAGE_SIZE - (addr & W1_PAGE_MASK);
		if (len > (count - idx))
			len = count - idx;

		if (w1_f23_write(sl, addr, len, &buf[idx]) < 0) {
			count = -EIO;
			goto out_up;
		}
		idx += len;
	}

out_up:
	mutex_unlock(&sl->master->bus_mutex);

	return count;
}