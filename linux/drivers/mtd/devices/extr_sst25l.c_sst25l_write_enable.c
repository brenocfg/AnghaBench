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
struct sst25l_flash {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int EROFS ; 
 unsigned char SST25L_CMD_EWSR ; 
 unsigned char SST25L_CMD_WRDI ; 
 unsigned char SST25L_CMD_WREN ; 
 unsigned char SST25L_CMD_WRSR ; 
 unsigned char SST25L_STATUS_BP0 ; 
 unsigned char SST25L_STATUS_BP1 ; 
 int SST25L_STATUS_WREN ; 
 int spi_write (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int sst25l_status (struct sst25l_flash*,int*) ; 

__attribute__((used)) static int sst25l_write_enable(struct sst25l_flash *flash, int enable)
{
	unsigned char command[2];
	int status, err;

	command[0] = enable ? SST25L_CMD_WREN : SST25L_CMD_WRDI;
	err = spi_write(flash->spi, command, 1);
	if (err)
		return err;

	command[0] = SST25L_CMD_EWSR;
	err = spi_write(flash->spi, command, 1);
	if (err)
		return err;

	command[0] = SST25L_CMD_WRSR;
	command[1] = enable ? 0 : SST25L_STATUS_BP0 | SST25L_STATUS_BP1;
	err = spi_write(flash->spi, command, 2);
	if (err)
		return err;

	if (enable) {
		err = sst25l_status(flash, &status);
		if (err)
			return err;
		if (!(status & SST25L_STATUS_WREN))
			return -EROFS;
	}

	return 0;
}