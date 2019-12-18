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
typedef  int u8 ;
struct w1_slave {int /*<<< orphan*/  master; } ;
struct w1_f1C_data {int validcrc; int /*<<< orphan*/ * memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC16_INIT ; 
 scalar_t__ CRC16_VALID ; 
 int EIO ; 
 int W1_F1C_READ_EEPROM ; 
 int W1_PAGE_SIZE ; 
 scalar_t__ crc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  w1_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int w1_f1C_refresh_block(struct w1_slave *sl, struct w1_f1C_data *data,
				int block)
{
	u8	wrbuf[3];
	int	off = block * W1_PAGE_SIZE;

	if (data->validcrc & (1 << block))
		return 0;

	if (w1_reset_select_slave(sl)) {
		data->validcrc = 0;
		return -EIO;
	}

	wrbuf[0] = W1_F1C_READ_EEPROM;
	wrbuf[1] = off & 0xff;
	wrbuf[2] = off >> 8;
	w1_write_block(sl->master, wrbuf, 3);
	w1_read_block(sl->master, &data->memory[off], W1_PAGE_SIZE);

	/* cache the block if the CRC is valid */
	if (crc16(CRC16_INIT, &data->memory[off], W1_PAGE_SIZE) == CRC16_VALID)
		data->validcrc |= (1 << block);

	return 0;
}