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
struct mtk_eth {int /*<<< orphan*/  tx_irq_lock; int /*<<< orphan*/  tx_int_mask_reg; } ;

/* Variables and functions */
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void mtk_tx_irq_enable(struct mtk_eth *eth, u32 mask)
{
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&eth->tx_irq_lock, flags);
	val = mtk_r32(eth, eth->tx_int_mask_reg);
	mtk_w32(eth, val | mask, eth->tx_int_mask_reg);
	spin_unlock_irqrestore(&eth->tx_irq_lock, flags);
}