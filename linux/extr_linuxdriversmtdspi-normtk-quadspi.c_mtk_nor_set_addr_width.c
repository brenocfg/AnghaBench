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
struct spi_nor {int addr_width; } ;
struct mtk_nor {scalar_t__ base; int /*<<< orphan*/  dev; struct spi_nor nor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_NOR_4B_ADDR_EN ; 
 scalar_t__ MTK_NOR_DUAL_REG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_nor_set_addr_width(struct mtk_nor *mtk_nor)
{
	u8 val;
	struct spi_nor *nor = &mtk_nor->nor;

	val = readb(mtk_nor->base + MTK_NOR_DUAL_REG);

	switch (nor->addr_width) {
	case 3:
		val &= ~MTK_NOR_4B_ADDR_EN;
		break;
	case 4:
		val |= MTK_NOR_4B_ADDR_EN;
		break;
	default:
		dev_warn(mtk_nor->dev, "Unexpected address width %u.\n",
			 nor->addr_width);
		break;
	}

	writeb(val, mtk_nor->base + MTK_NOR_DUAL_REG);
}