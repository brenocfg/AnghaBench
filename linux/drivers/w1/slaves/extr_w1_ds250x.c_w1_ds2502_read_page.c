#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct w1_slave {TYPE_1__* master; struct w1_eprom_data* family_data; } ;
struct w1_eprom_data {scalar_t__* eprom; int /*<<< orphan*/  page_present; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int EIO ; 
 int W1_PAGE_SIZE ; 
 scalar_t__ W1_READ_DATA_CRC ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ w1_calc_crc8 (scalar_t__*,int) ; 
 scalar_t__ w1_read_8 (TYPE_1__*) ; 
 int /*<<< orphan*/  w1_read_block (TYPE_1__*,scalar_t__*,int) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,scalar_t__*,int) ; 

__attribute__((used)) static int w1_ds2502_read_page(struct w1_slave *sl, int pageno)
{
	struct w1_eprom_data *data = sl->family_data;
	int pgoff = pageno * W1_PAGE_SIZE;
	int ret = -EIO;
	u8 buf[3];
	u8 crc8;

	if (test_bit(pageno, data->page_present))
		return 0; /* page already present */

	mutex_lock(&sl->master->bus_mutex);

	if (w1_reset_select_slave(sl))
		goto err;

	buf[0] = W1_READ_DATA_CRC;
	buf[1] = pgoff & 0xff;
	buf[2] = pgoff >> 8;
	w1_write_block(sl->master, buf, 3);

	crc8 = w1_read_8(sl->master);
	if (w1_calc_crc8(buf, 3) != crc8)
		goto err;

	w1_read_block(sl->master, &data->eprom[pgoff], W1_PAGE_SIZE);

	crc8 = w1_read_8(sl->master);
	if (w1_calc_crc8(&data->eprom[pgoff], W1_PAGE_SIZE) != crc8)
		goto err;

	set_bit(pageno, data->page_present); /* mark page present */
	ret = 0;
err:
	mutex_unlock(&sl->master->bus_mutex);
	return ret;
}