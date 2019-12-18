#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {int read_dummy; int /*<<< orphan*/  read_proto; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  read_opcode; } ;
struct TYPE_8__ {int buswidth; int nbytes; } ;
struct TYPE_7__ {int /*<<< orphan*/  buswidth; } ;
struct TYPE_6__ {int buswidth; } ;
struct TYPE_5__ {int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_4__ dummy; TYPE_3__ data; TYPE_2__ addr; TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DATA_IN (size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DUMMY (int,int) ; 
 int spi_nor_get_protocol_addr_nbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_get_protocol_data_nbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_get_protocol_inst_nbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_spimem_xfer_data (struct spi_nor*,struct spi_mem_op*) ; 

__attribute__((used)) static ssize_t spi_nor_spimem_read_data(struct spi_nor *nor, loff_t from,
					size_t len, u8 *buf)
{
	struct spi_mem_op op =
		SPI_MEM_OP(SPI_MEM_OP_CMD(nor->read_opcode, 1),
			   SPI_MEM_OP_ADDR(nor->addr_width, from, 1),
			   SPI_MEM_OP_DUMMY(nor->read_dummy, 1),
			   SPI_MEM_OP_DATA_IN(len, buf, 1));

	/* get transfer protocols. */
	op.cmd.buswidth = spi_nor_get_protocol_inst_nbits(nor->read_proto);
	op.addr.buswidth = spi_nor_get_protocol_addr_nbits(nor->read_proto);
	op.dummy.buswidth = op.addr.buswidth;
	op.data.buswidth = spi_nor_get_protocol_data_nbits(nor->read_proto);

	/* convert the dummy cycles to the number of bytes */
	op.dummy.nbytes = (nor->read_dummy * op.dummy.buswidth) / 8;

	return spi_nor_spimem_xfer_data(nor, &op);
}