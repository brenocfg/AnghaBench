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
struct nixge_priv {scalar_t__ dma_regs; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nixge_dma_write_desc_reg(struct nixge_priv *priv, off_t offset,
				     dma_addr_t addr)
{
	writel(lower_32_bits(addr), priv->dma_regs + offset);
#ifdef CONFIG_PHYS_ADDR_T_64BIT
	writel(upper_32_bits(addr), priv->dma_regs + offset + 4);
#endif
}