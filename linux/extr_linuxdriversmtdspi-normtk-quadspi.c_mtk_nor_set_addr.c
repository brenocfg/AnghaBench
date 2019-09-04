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
typedef  int u32 ;
struct mtk_nor {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MTK_NOR_RADR0_REG ; 
 scalar_t__ MTK_NOR_RADR3_REG ; 
 int /*<<< orphan*/  mtk_nor_set_addr_width (struct mtk_nor*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void mtk_nor_set_addr(struct mtk_nor *mtk_nor, u32 addr)
{
	int i;

	mtk_nor_set_addr_width(mtk_nor);

	for (i = 0; i < 3; i++) {
		writeb(addr & 0xff, mtk_nor->base + MTK_NOR_RADR0_REG + i * 4);
		addr >>= 8;
	}
	/* Last register is non-contiguous */
	writeb(addr & 0xff, mtk_nor->base + MTK_NOR_RADR3_REG);
}