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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_femac_priv {scalar_t__ glb_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MACFLT_ENA ; 
 scalar_t__ GLB_MAC_H16 (unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hisi_femac_enable_hw_addr_filter(struct hisi_femac_priv *priv,
					     unsigned int reg_n, bool enable)
{
	u32 val;

	val = readl(priv->glb_base + GLB_MAC_H16(reg_n));
	if (enable)
		val |= BIT_MACFLT_ENA;
	else
		val &= ~BIT_MACFLT_ENA;
	writel(val, priv->glb_base + GLB_MAC_H16(reg_n));
}