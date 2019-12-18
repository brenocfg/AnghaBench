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
struct spi_nor {int read_proto; int /*<<< orphan*/  read_opcode; } ;
struct mtk_nor {scalar_t__ base; struct spi_nor nor; } ;

/* Variables and functions */
 scalar_t__ MTK_NOR_CFG1_REG ; 
 int /*<<< orphan*/  MTK_NOR_DUAL_DISABLE ; 
 int /*<<< orphan*/  MTK_NOR_DUAL_READ_EN ; 
 scalar_t__ MTK_NOR_DUAL_REG ; 
 int /*<<< orphan*/  MTK_NOR_FAST_READ ; 
 scalar_t__ MTK_NOR_PRGDATA3_REG ; 
 scalar_t__ MTK_NOR_PRGDATA4_REG ; 
 int /*<<< orphan*/  MTK_NOR_QUAD_READ_EN ; 
#define  SNOR_PROTO_1_1_1 130 
#define  SNOR_PROTO_1_1_2 129 
#define  SNOR_PROTO_1_1_4 128 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_nor_set_read_mode(struct mtk_nor *mtk_nor)
{
	struct spi_nor *nor = &mtk_nor->nor;

	switch (nor->read_proto) {
	case SNOR_PROTO_1_1_1:
		writeb(nor->read_opcode, mtk_nor->base +
		       MTK_NOR_PRGDATA3_REG);
		writeb(MTK_NOR_FAST_READ, mtk_nor->base +
		       MTK_NOR_CFG1_REG);
		break;
	case SNOR_PROTO_1_1_2:
		writeb(nor->read_opcode, mtk_nor->base +
		       MTK_NOR_PRGDATA3_REG);
		writeb(MTK_NOR_DUAL_READ_EN, mtk_nor->base +
		       MTK_NOR_DUAL_REG);
		break;
	case SNOR_PROTO_1_1_4:
		writeb(nor->read_opcode, mtk_nor->base +
		       MTK_NOR_PRGDATA4_REG);
		writeb(MTK_NOR_QUAD_READ_EN, mtk_nor->base +
		       MTK_NOR_DUAL_REG);
		break;
	default:
		writeb(MTK_NOR_DUAL_DISABLE, mtk_nor->base +
		       MTK_NOR_DUAL_REG);
		break;
	}
}