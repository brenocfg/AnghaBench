#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_11__ {int* out; int /*<<< orphan*/ * in; } ;
struct TYPE_12__ {int nbytes; scalar_t__ dir; TYPE_5__ buf; int /*<<< orphan*/  buswidth; } ;
struct TYPE_10__ {int nbytes; } ;
struct TYPE_9__ {int nbytes; int val; int /*<<< orphan*/  buswidth; } ;
struct TYPE_8__ {int opcode; int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_6__ data; TYPE_4__ dummy; TYPE_3__ addr; TYPE_2__ cmd; } ;
struct spi_mem {TYPE_1__* spi; } ;
struct mxic_spi {scalar_t__ regs; } ;
struct TYPE_7__ {int mode; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 scalar_t__ HC_CFG ; 
 int HC_CFG_IDLE_SIO_LVL (int) ; 
 int HC_CFG_MAN_CS_ASSERT ; 
 int HC_CFG_MAN_CS_EN ; 
 int HC_CFG_NIO (int) ; 
 int HC_CFG_SLV_ACT (int /*<<< orphan*/ ) ; 
 int HC_CFG_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HC_CFG_TYPE_SPI_NOR ; 
 scalar_t__ HC_EN ; 
 int HC_EN_BIT ; 
 int OP_ADDR_BUSW (scalar_t__) ; 
 int OP_ADDR_BYTES (int) ; 
 int OP_CMD_BUSW (scalar_t__) ; 
 int OP_CMD_BYTES (int) ; 
 int OP_DATA_BUSW (scalar_t__) ; 
 int OP_DUMMY_CYC (int) ; 
 int OP_READ ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 scalar_t__ SPI_MEM_DATA_OUT ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 scalar_t__ SS_CTRL (int /*<<< orphan*/ ) ; 
 scalar_t__ fls (int /*<<< orphan*/ ) ; 
 int mxic_spi_data_xfer (struct mxic_spi*,int*,int /*<<< orphan*/ *,int) ; 
 int mxic_spi_set_freq (struct mxic_spi*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct mxic_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxic_spi_mem_exec_op(struct spi_mem *mem,
				const struct spi_mem_op *op)
{
	struct mxic_spi *mxic = spi_master_get_devdata(mem->spi->master);
	int nio = 1, i, ret;
	u32 ss_ctrl;
	u8 addr[8];

	ret = mxic_spi_set_freq(mxic, mem->spi->max_speed_hz);
	if (ret)
		return ret;

	if (mem->spi->mode & (SPI_TX_QUAD | SPI_RX_QUAD))
		nio = 4;
	else if (mem->spi->mode & (SPI_TX_DUAL | SPI_RX_DUAL))
		nio = 2;

	writel(HC_CFG_NIO(nio) |
	       HC_CFG_TYPE(mem->spi->chip_select, HC_CFG_TYPE_SPI_NOR) |
	       HC_CFG_SLV_ACT(mem->spi->chip_select) | HC_CFG_IDLE_SIO_LVL(1) |
	       HC_CFG_MAN_CS_EN,
	       mxic->regs + HC_CFG);
	writel(HC_EN_BIT, mxic->regs + HC_EN);

	ss_ctrl = OP_CMD_BYTES(1) | OP_CMD_BUSW(fls(op->cmd.buswidth) - 1);

	if (op->addr.nbytes)
		ss_ctrl |= OP_ADDR_BYTES(op->addr.nbytes) |
			   OP_ADDR_BUSW(fls(op->addr.buswidth) - 1);

	if (op->dummy.nbytes)
		ss_ctrl |= OP_DUMMY_CYC(op->dummy.nbytes);

	if (op->data.nbytes) {
		ss_ctrl |= OP_DATA_BUSW(fls(op->data.buswidth) - 1);
		if (op->data.dir == SPI_MEM_DATA_IN)
			ss_ctrl |= OP_READ;
	}

	writel(ss_ctrl, mxic->regs + SS_CTRL(mem->spi->chip_select));

	writel(readl(mxic->regs + HC_CFG) | HC_CFG_MAN_CS_ASSERT,
	       mxic->regs + HC_CFG);

	ret = mxic_spi_data_xfer(mxic, &op->cmd.opcode, NULL, 1);
	if (ret)
		goto out;

	for (i = 0; i < op->addr.nbytes; i++)
		addr[i] = op->addr.val >> (8 * (op->addr.nbytes - i - 1));

	ret = mxic_spi_data_xfer(mxic, addr, NULL, op->addr.nbytes);
	if (ret)
		goto out;

	ret = mxic_spi_data_xfer(mxic, NULL, NULL, op->dummy.nbytes);
	if (ret)
		goto out;

	ret = mxic_spi_data_xfer(mxic,
				 op->data.dir == SPI_MEM_DATA_OUT ?
				 op->data.buf.out : NULL,
				 op->data.dir == SPI_MEM_DATA_IN ?
				 op->data.buf.in : NULL,
				 op->data.nbytes);

out:
	writel(readl(mxic->regs + HC_CFG) & ~HC_CFG_MAN_CS_ASSERT,
	       mxic->regs + HC_CFG);
	writel(0, mxic->regs + HC_EN);

	return ret;
}