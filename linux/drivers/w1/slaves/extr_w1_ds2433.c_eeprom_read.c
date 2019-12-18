#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct w1_slave {TYPE_1__* master; struct w1_f23_data* family_data; } ;
struct w1_f23_data {int /*<<< orphan*/ * memory; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;
struct TYPE_3__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 size_t EIO ; 
 int /*<<< orphan*/  W1_EEPROM_SIZE ; 
 size_t W1_F23_READ_EEPROM ; 
 size_t W1_PAGE_BITS ; 
 struct w1_slave* kobj_to_w1_slave (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t w1_f23_fix_count (size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ w1_f23_refresh_block (struct w1_slave*,struct w1_f23_data*,int) ; 
 int /*<<< orphan*/  w1_read_block (TYPE_1__*,char*,size_t) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,size_t*,int) ; 

__attribute__((used)) static ssize_t eeprom_read(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr, char *buf,
			   loff_t off, size_t count)
{
	struct w1_slave *sl = kobj_to_w1_slave(kobj);
#ifdef CONFIG_W1_SLAVE_DS2433_CRC
	struct w1_f23_data *data = sl->family_data;
	int i, min_page, max_page;
#else
	u8 wrbuf[3];
#endif

	if ((count = w1_f23_fix_count(off, count, W1_EEPROM_SIZE)) == 0)
		return 0;

	mutex_lock(&sl->master->bus_mutex);

#ifdef CONFIG_W1_SLAVE_DS2433_CRC

	min_page = (off >> W1_PAGE_BITS);
	max_page = (off + count - 1) >> W1_PAGE_BITS;
	for (i = min_page; i <= max_page; i++) {
		if (w1_f23_refresh_block(sl, data, i)) {
			count = -EIO;
			goto out_up;
		}
	}
	memcpy(buf, &data->memory[off], count);

#else 	/* CONFIG_W1_SLAVE_DS2433_CRC */

	/* read directly from the EEPROM */
	if (w1_reset_select_slave(sl)) {
		count = -EIO;
		goto out_up;
	}

	wrbuf[0] = W1_F23_READ_EEPROM;
	wrbuf[1] = off & 0xff;
	wrbuf[2] = off >> 8;
	w1_write_block(sl->master, wrbuf, 3);
	w1_read_block(sl->master, buf, count);

#endif	/* CONFIG_W1_SLAVE_DS2433_CRC */

out_up:
	mutex_unlock(&sl->master->bus_mutex);

	return count;
}