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
struct hip04_priv {scalar_t__ base; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int PPE_BUF_SIZE_SHIFT ; 
 scalar_t__ PPE_CFG_CPU_ADD_ADDR ; 
 int PPE_TX_BUF_HOLD ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hip04_set_xmit_desc(struct hip04_priv *priv, dma_addr_t phys)
{
	u32 val;

	val = phys >> PPE_BUF_SIZE_SHIFT | PPE_TX_BUF_HOLD;
	writel(val, priv->base + PPE_CFG_CPU_ADD_ADDR);
}