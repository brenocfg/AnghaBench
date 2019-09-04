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
struct bcm_sysport_priv {scalar_t__ is_lite; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPD_EN ; 
 int /*<<< orphan*/  RBUF_ACPI_EN ; 
 int /*<<< orphan*/  RBUF_ACPI_EN_LITE ; 
 int /*<<< orphan*/  RBUF_CONTROL ; 
 int /*<<< orphan*/  UMAC_MPD_CTRL ; 
 int /*<<< orphan*/  rbuf_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuf_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpd_enable_set(struct bcm_sysport_priv *priv, bool enable)
{
	u32 reg, bit;

	reg = umac_readl(priv, UMAC_MPD_CTRL);
	if (enable)
		reg |= MPD_EN;
	else
		reg &= ~MPD_EN;
	umac_writel(priv, reg, UMAC_MPD_CTRL);

	if (priv->is_lite)
		bit = RBUF_ACPI_EN_LITE;
	else
		bit = RBUF_ACPI_EN;

	reg = rbuf_readl(priv, RBUF_CONTROL);
	if (enable)
		reg |= bit;
	else
		reg &= ~bit;
	rbuf_writel(priv, reg, RBUF_CONTROL);
}