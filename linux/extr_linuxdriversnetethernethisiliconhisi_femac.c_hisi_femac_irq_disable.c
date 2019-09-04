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
struct hisi_femac_priv {scalar_t__ glb_base; } ;

/* Variables and functions */
 scalar_t__ GLB_IRQ_ENA ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hisi_femac_irq_disable(struct hisi_femac_priv *priv, int irqs)
{
	u32 val;

	val = readl(priv->glb_base + GLB_IRQ_ENA);
	writel(val & (~irqs), priv->glb_base + GLB_IRQ_ENA);
}