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
typedef  int u32 ;
struct spi_nor {int (* erase ) (struct spi_nor*,int) ;int addr_width; int* bouncebuf; int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  erase_opcode; scalar_t__ spimem; } ;
struct spi_mem_op {int dummy; } ;

/* Variables and functions */
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_ADDR (int,int,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_DATA ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_DUMMY ; 
 int spi_mem_exec_op (scalar_t__,struct spi_mem_op*) ; 
 int spi_nor_convert_addr (struct spi_nor*,int) ; 
 int stub1 (struct spi_nor*,int) ; 
 int stub2 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int spi_nor_erase_sector(struct spi_nor *nor, u32 addr)
{
	int i;

	addr = spi_nor_convert_addr(nor, addr);

	if (nor->erase)
		return nor->erase(nor, addr);

	if (nor->spimem) {
		struct spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(nor->erase_opcode, 1),
				   SPI_MEM_OP_ADDR(nor->addr_width, addr, 1),
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_NO_DATA);

		return spi_mem_exec_op(nor->spimem, &op);
	}

	/*
	 * Default implementation, if driver doesn't have a specialized HW
	 * control
	 */
	for (i = nor->addr_width - 1; i >= 0; i--) {
		nor->bouncebuf[i] = addr & 0xff;
		addr >>= 8;
	}

	return nor->write_reg(nor, nor->erase_opcode, nor->bouncebuf,
			      nor->addr_width);
}