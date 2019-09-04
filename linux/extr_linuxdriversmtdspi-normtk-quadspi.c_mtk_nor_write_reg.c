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
struct mtk_nor {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SPINOR_OP_WRSR 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int mtk_nor_do_tx_rx (struct mtk_nor*,int,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mtk_nor_wr_sr (struct mtk_nor*,int) ; 

__attribute__((used)) static int mtk_nor_write_reg(struct spi_nor *nor, u8 opcode, u8 *buf,
			     int len)
{
	int ret;
	struct mtk_nor *mtk_nor = nor->priv;

	switch (opcode) {
	case SPINOR_OP_WRSR:
		/* We only handle 1 byte */
		ret = mtk_nor_wr_sr(mtk_nor, *buf);
		break;
	default:
		ret = mtk_nor_do_tx_rx(mtk_nor, opcode, buf, len, NULL, 0);
		if (ret)
			dev_warn(mtk_nor->dev, "write reg failure!\n");
		break;
	}
	return ret;
}