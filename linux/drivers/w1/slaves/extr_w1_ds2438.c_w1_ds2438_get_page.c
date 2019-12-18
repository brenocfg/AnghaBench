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
typedef  scalar_t__ u8 ;
struct w1_slave {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int DS2438_PAGE_SIZE ; 
 scalar_t__ W1_DS2438_READ_SCRATCH ; 
 scalar_t__ W1_DS2438_RECALL_MEMORY ; 
 unsigned int W1_DS2438_RETRIES ; 
 scalar_t__ w1_calc_crc8 (scalar_t__*,int) ; 
 size_t w1_read_block (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int w1_ds2438_get_page(struct w1_slave *sl, int pageno, u8 *buf)
{
	unsigned int retries = W1_DS2438_RETRIES;
	u8 w1_buf[2];
	u8 crc;
	size_t count;

	while (retries--) {
		crc = 0;

		if (w1_reset_select_slave(sl))
			continue;
		w1_buf[0] = W1_DS2438_RECALL_MEMORY;
		w1_buf[1] = 0x00;
		w1_write_block(sl->master, w1_buf, 2);

		if (w1_reset_select_slave(sl))
			continue;
		w1_buf[0] = W1_DS2438_READ_SCRATCH;
		w1_buf[1] = 0x00;
		w1_write_block(sl->master, w1_buf, 2);

		count = w1_read_block(sl->master, buf, DS2438_PAGE_SIZE + 1);
		if (count == DS2438_PAGE_SIZE + 1) {
			crc = w1_calc_crc8(buf, DS2438_PAGE_SIZE);

			/* check for correct CRC */
			if ((u8)buf[DS2438_PAGE_SIZE] == crc)
				return 0;
		}
	}
	return -1;
}