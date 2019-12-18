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
typedef  int uint32_t ;
struct sst25l_flash {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 unsigned char SST25L_CMD_SECTOR_ERASE ; 
 int spi_write (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int sst25l_wait_till_ready (struct sst25l_flash*) ; 
 int sst25l_write_enable (struct sst25l_flash*,int) ; 

__attribute__((used)) static int sst25l_erase_sector(struct sst25l_flash *flash, uint32_t offset)
{
	unsigned char command[4];
	int err;

	err = sst25l_write_enable(flash, 1);
	if (err)
		return err;

	command[0] = SST25L_CMD_SECTOR_ERASE;
	command[1] = offset >> 16;
	command[2] = offset >> 8;
	command[3] = offset;
	err = spi_write(flash->spi, command, 4);
	if (err)
		return err;

	err = sst25l_wait_till_ready(flash);
	if (err)
		return err;

	return sst25l_write_enable(flash, 0);
}