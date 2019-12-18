#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_nor_pp_command {int /*<<< orphan*/  proto; int /*<<< orphan*/  opcode; } ;
struct spi_nor {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  buswidth; } ;
struct TYPE_4__ {int /*<<< orphan*/  buswidth; } ;
struct TYPE_6__ {int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_2__ data; TYPE_1__ addr; TYPE_3__ cmd; } ;

/* Variables and functions */
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_ADDR (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DATA_OUT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_DUMMY ; 
 int /*<<< orphan*/  spi_nor_get_protocol_addr_nbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_get_protocol_data_nbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_get_protocol_inst_nbits (int /*<<< orphan*/ ) ; 
 int spi_nor_spimem_check_op (struct spi_nor*,struct spi_mem_op*) ; 

__attribute__((used)) static int spi_nor_spimem_check_pp(struct spi_nor *nor,
				   const struct spi_nor_pp_command *pp)
{
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(pp->opcode, 1),
					  SPI_MEM_OP_ADDR(3, 0, 1),
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_OUT(0, NULL, 1));

	op.cmd.buswidth = spi_nor_get_protocol_inst_nbits(pp->proto);
	op.addr.buswidth = spi_nor_get_protocol_addr_nbits(pp->proto);
	op.data.buswidth = spi_nor_get_protocol_data_nbits(pp->proto);

	return spi_nor_spimem_check_op(nor, &op);
}