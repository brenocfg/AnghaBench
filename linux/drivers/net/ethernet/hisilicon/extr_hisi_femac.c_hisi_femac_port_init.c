#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hisi_femac_priv {scalar_t__ port_base; scalar_t__ glb_base; TYPE_2__* ndev; } ;
struct TYPE_4__ {TYPE_1__* phydev; } ;
struct TYPE_3__ {scalar_t__ interface; } ;

/* Variables and functions */
 int FWCTRL_FW2CPU_ENA ; 
 int FWCTRL_FWALL2CPU ; 
 int FWCTRL_VLAN_ENABLE ; 
 scalar_t__ GLB_FWCTRL ; 
 scalar_t__ GLB_IRQ_RAW ; 
 scalar_t__ GLB_MACTCTRL ; 
 int HW_RX_FIFO_DEPTH ; 
 int HW_TX_FIFO_DEPTH ; 
 int IRQ_ENA_PORT0 ; 
 int IRQ_ENA_PORT0_MASK ; 
 int MACTCTRL_BROAD2CPU ; 
 int MACTCTRL_MACT_ENA ; 
 scalar_t__ MAC_PORTSEL ; 
 int MAC_PORTSEL_RMII ; 
 int MAC_PORTSEL_STAT_CPU ; 
 scalar_t__ MAC_SET ; 
 int MAX_FRAME_SIZE ; 
 int MAX_FRAME_SIZE_MASK ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 scalar_t__ QLEN_SET ; 
 int RX_COALESCED_FRAMES ; 
 int RX_COALESCED_FRAME_OFFSET ; 
 int RX_COALESCED_TIMER ; 
 scalar_t__ RX_COALESCE_SET ; 
 int RX_DEPTH_OFFSET ; 
 int /*<<< orphan*/  hisi_femac_irq_disable (struct hisi_femac_priv*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hisi_femac_port_init(struct hisi_femac_priv *priv)
{
	u32 val;

	/* MAC gets link status info and phy mode by software config */
	val = MAC_PORTSEL_STAT_CPU;
	if (priv->ndev->phydev->interface == PHY_INTERFACE_MODE_RMII)
		val |= MAC_PORTSEL_RMII;
	writel(val, priv->port_base + MAC_PORTSEL);

	/*clear all interrupt status */
	writel(IRQ_ENA_PORT0_MASK, priv->glb_base + GLB_IRQ_RAW);
	hisi_femac_irq_disable(priv, IRQ_ENA_PORT0_MASK | IRQ_ENA_PORT0);

	val = readl(priv->glb_base + GLB_FWCTRL);
	val &= ~(FWCTRL_VLAN_ENABLE | FWCTRL_FWALL2CPU);
	val |= FWCTRL_FW2CPU_ENA;
	writel(val, priv->glb_base + GLB_FWCTRL);

	val = readl(priv->glb_base + GLB_MACTCTRL);
	val |= (MACTCTRL_BROAD2CPU | MACTCTRL_MACT_ENA);
	writel(val, priv->glb_base + GLB_MACTCTRL);

	val = readl(priv->port_base + MAC_SET);
	val &= ~MAX_FRAME_SIZE_MASK;
	val |= MAX_FRAME_SIZE;
	writel(val, priv->port_base + MAC_SET);

	val = RX_COALESCED_TIMER |
		(RX_COALESCED_FRAMES << RX_COALESCED_FRAME_OFFSET);
	writel(val, priv->port_base + RX_COALESCE_SET);

	val = (HW_RX_FIFO_DEPTH << RX_DEPTH_OFFSET) | HW_TX_FIFO_DEPTH;
	writel(val, priv->port_base + QLEN_SET);
}