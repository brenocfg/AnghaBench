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
typedef  int /*<<< orphan*/  u_char ;
struct spi_nor {scalar_t__ program_opcode; scalar_t__ sst_write_second; int /*<<< orphan*/  write_proto; int /*<<< orphan*/  addr_width; struct m25p* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  out; } ;
struct TYPE_8__ {size_t nbytes; TYPE_3__ buf; int /*<<< orphan*/  buswidth; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; scalar_t__ nbytes; int /*<<< orphan*/  buswidth; } ;
struct TYPE_5__ {int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_4__ data; TYPE_2__ addr; TYPE_1__ cmd; } ;
struct m25p {int /*<<< orphan*/  spimem; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ SPINOR_OP_AAI_WP ; 
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (scalar_t__,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DATA_OUT (size_t,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_DUMMY ; 
 size_t UINT_MAX ; 
 int spi_mem_adjust_op_size (int /*<<< orphan*/ ,struct spi_mem_op*) ; 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 
 int /*<<< orphan*/  spi_nor_get_protocol_addr_nbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_get_protocol_data_nbits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_nor_get_protocol_inst_nbits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t m25p80_write(struct spi_nor *nor, loff_t to, size_t len,
			    const u_char *buf)
{
	struct m25p *flash = nor->priv;
	struct spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(nor->program_opcode, 1),
				   SPI_MEM_OP_ADDR(nor->addr_width, to, 1),
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(len, buf, 1));
	size_t remaining = len;
	int ret;

	/* get transfer protocols. */
	op.cmd.buswidth = spi_nor_get_protocol_inst_nbits(nor->write_proto);
	op.addr.buswidth = spi_nor_get_protocol_addr_nbits(nor->write_proto);
	op.data.buswidth = spi_nor_get_protocol_data_nbits(nor->write_proto);

	if (nor->program_opcode == SPINOR_OP_AAI_WP && nor->sst_write_second)
		op.addr.nbytes = 0;

	while (remaining) {
		op.data.nbytes = remaining < UINT_MAX ? remaining : UINT_MAX;
		ret = spi_mem_adjust_op_size(flash->spimem, &op);
		if (ret)
			return ret;

		ret = spi_mem_exec_op(flash->spimem, &op);
		if (ret)
			return ret;

		op.addr.val += op.data.nbytes;
		remaining -= op.data.nbytes;
		op.data.buf.out += op.data.nbytes;
	}

	return len;
}