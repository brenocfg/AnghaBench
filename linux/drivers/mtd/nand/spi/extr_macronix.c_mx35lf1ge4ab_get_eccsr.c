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
typedef  int /*<<< orphan*/  u8 ;
struct spinand_device {int /*<<< orphan*/  spimem; } ;
struct spi_mem_op {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACRONIX_ECCSR_MASK ; 
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (int,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DATA_IN (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DUMMY (int,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_ADDR ; 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 

__attribute__((used)) static int mx35lf1ge4ab_get_eccsr(struct spinand_device *spinand, u8 *eccsr)
{
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0x7c, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_DUMMY(1, 1),
					  SPI_MEM_OP_DATA_IN(1, eccsr, 1));

	int ret = spi_mem_exec_op(spinand->spimem, &op);
	if (ret)
		return ret;

	*eccsr &= MACRONIX_ECCSR_MASK;
	return 0;
}