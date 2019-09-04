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
struct mtk_nor {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MTK_NOR_CFG2_REG ; 
 int MTK_NOR_WR_BUF_DISABLE ; 
 int readb_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_nor_write_buffer_disable(struct mtk_nor *mtk_nor)
{
	u8 reg;

	writel(MTK_NOR_WR_BUF_DISABLE, mtk_nor->base + MTK_NOR_CFG2_REG);
	return readb_poll_timeout(mtk_nor->base + MTK_NOR_CFG2_REG, reg,
				  MTK_NOR_WR_BUF_DISABLE == (reg & 0x1), 100,
				  10000);
}