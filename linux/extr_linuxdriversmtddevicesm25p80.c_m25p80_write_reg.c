#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {struct m25p* priv; } ;
struct TYPE_4__ {void* out; } ;
struct TYPE_3__ {TYPE_2__ buf; } ;
struct spi_mem_op {TYPE_1__ data; } ;
struct m25p {int /*<<< orphan*/  spimem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DATA_OUT (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_ADDR ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_DUMMY ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int spi_mem_exec_op (int /*<<< orphan*/ ,struct spi_mem_op*) ; 

__attribute__((used)) static int m25p80_write_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	struct m25p *flash = nor->priv;
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(opcode, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_OUT(len, NULL, 1));
	void *scratchbuf;
	int ret;

	scratchbuf = kmemdup(buf, len, GFP_KERNEL);
	if (!scratchbuf)
		return -ENOMEM;

	op.data.buf.out = scratchbuf;
	ret = spi_mem_exec_op(flash->spimem, &op);
	kfree(scratchbuf);

	return ret;
}