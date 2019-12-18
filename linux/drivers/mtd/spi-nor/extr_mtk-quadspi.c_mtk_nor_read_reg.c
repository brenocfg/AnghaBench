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
struct spi_nor {struct mtk_nor* priv; } ;
struct mtk_nor {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_NOR_RDSR_CMD ; 
 scalar_t__ MTK_NOR_RDSR_REG ; 
#define  SPINOR_OP_RDSR 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mtk_nor_do_tx_rx (struct mtk_nor*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int mtk_nor_execute_cmd (struct mtk_nor*,int /*<<< orphan*/ ) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static int mtk_nor_read_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	int ret;
	struct mtk_nor *mtk_nor = nor->priv;

	switch (opcode) {
	case SPINOR_OP_RDSR:
		ret = mtk_nor_execute_cmd(mtk_nor, MTK_NOR_RDSR_CMD);
		if (ret < 0)
			return ret;
		if (len == 1)
			*buf = readb(mtk_nor->base + MTK_NOR_RDSR_REG);
		else
			dev_err(mtk_nor->dev, "len should be 1 for read status!\n");
		break;
	default:
		ret = mtk_nor_do_tx_rx(mtk_nor, opcode, NULL, 0, buf, len);
		break;
	}
	return ret;
}