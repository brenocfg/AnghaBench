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
typedef  int u32 ;
struct spi_nor {int flags; int (* erase ) (struct spi_nor*,int) ;int addr_width; int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  erase_opcode; } ;

/* Variables and functions */
 int SNOR_F_S3AN_ADDR_DEFAULT ; 
 int SPI_NOR_MAX_ADDR_WIDTH ; 
 int spi_nor_s3an_addr_convert (struct spi_nor*,int) ; 
 int stub1 (struct spi_nor*,int) ; 
 int stub2 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int spi_nor_erase_sector(struct spi_nor *nor, u32 addr)
{
	u8 buf[SPI_NOR_MAX_ADDR_WIDTH];
	int i;

	if (nor->flags & SNOR_F_S3AN_ADDR_DEFAULT)
		addr = spi_nor_s3an_addr_convert(nor, addr);

	if (nor->erase)
		return nor->erase(nor, addr);

	/*
	 * Default implementation, if driver doesn't have a specialized HW
	 * control
	 */
	for (i = nor->addr_width - 1; i >= 0; i--) {
		buf[i] = addr & 0xff;
		addr >>= 8;
	}

	return nor->write_reg(nor, nor->erase_opcode, buf, nor->addr_width);
}