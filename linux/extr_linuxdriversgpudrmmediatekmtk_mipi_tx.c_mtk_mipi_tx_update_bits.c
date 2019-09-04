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
struct mtk_mipi_tx {int regs; } ;

/* Variables and functions */
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void mtk_mipi_tx_update_bits(struct mtk_mipi_tx *mipi_tx, u32 offset,
				    u32 mask, u32 data)
{
	u32 temp = readl(mipi_tx->regs + offset);

	writel((temp & ~mask) | (data & mask), mipi_tx->regs + offset);
}