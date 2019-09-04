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
struct spi_nor {struct m25p* priv; } ;
struct TYPE_5__ {void* in; } ;
struct TYPE_6__ {TYPE_1__ buf; } ;
struct spi_mem_op {TYPE_2__ data; } ;
struct m25p {TYPE_4__* spimem; } ;
struct TYPE_8__ {TYPE_3__* spi; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct spi_mem_op SPI_MEM_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MEM_OP_CMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_DATA_IN (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_ADDR ; 
 int /*<<< orphan*/  SPI_MEM_OP_NO_DUMMY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int spi_mem_exec_op (TYPE_4__*,struct spi_mem_op*) ; 

__attribute__((used)) static int m25p80_read_reg(struct spi_nor *nor, u8 code, u8 *val, int len)
{
	struct m25p *flash = nor->priv;
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(code, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_IN(len, NULL, 1));
	void *scratchbuf;
	int ret;

	scratchbuf = kmalloc(len, GFP_KERNEL);
	if (!scratchbuf)
		return -ENOMEM;

	op.data.buf.in = scratchbuf;
	ret = spi_mem_exec_op(flash->spimem, &op);
	if (ret < 0)
		dev_err(&flash->spimem->spi->dev, "error %d reading %x\n", ret,
			code);
	else
		memcpy(val, scratchbuf, len);

	kfree(scratchbuf);

	return ret;
}