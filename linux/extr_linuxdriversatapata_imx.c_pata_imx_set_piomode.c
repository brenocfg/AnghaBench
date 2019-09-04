#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pata_imx_priv {scalar_t__ host_regs; } ;
struct ata_port {TYPE_1__* host; } ;
struct ata_device {int dummy; } ;
struct TYPE_2__ {struct pata_imx_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ PATA_IMX_ATA_CONTROL ; 
 int /*<<< orphan*/  PATA_IMX_ATA_CTRL_IORDY_EN ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  pata_imx_set_timing (struct ata_device*,struct pata_imx_priv*) ; 

__attribute__((used)) static void pata_imx_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct pata_imx_priv *priv = ap->host->private_data;
	u32 val;

	pata_imx_set_timing(adev, priv);

	val = __raw_readl(priv->host_regs + PATA_IMX_ATA_CONTROL);
	if (ata_pio_need_iordy(adev))
		val |= PATA_IMX_ATA_CTRL_IORDY_EN;
	else
		val &= ~PATA_IMX_ATA_CTRL_IORDY_EN;
	__raw_writel(val, priv->host_regs + PATA_IMX_ATA_CONTROL);
}