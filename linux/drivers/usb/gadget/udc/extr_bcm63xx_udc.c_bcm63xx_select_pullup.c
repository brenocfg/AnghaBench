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
typedef  int u32 ;
struct bcm63xx_udc {TYPE_1__* pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_no; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSET_USBH_PRIV ; 
 int /*<<< orphan*/  USBH_PRIV_UTMI_CTL_6368_REG ; 
 int USBH_PRIV_UTMI_CTL_NODRIV_SHIFT ; 
 int bcm_rset_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_rset_writel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_select_pullup(struct bcm63xx_udc *udc, bool is_on)
{
	u32 val, portmask = BIT(udc->pd->port_no);

	val = bcm_rset_readl(RSET_USBH_PRIV, USBH_PRIV_UTMI_CTL_6368_REG);
	if (is_on)
		val &= ~(portmask << USBH_PRIV_UTMI_CTL_NODRIV_SHIFT);
	else
		val |= (portmask << USBH_PRIV_UTMI_CTL_NODRIV_SHIFT);
	bcm_rset_writel(RSET_USBH_PRIV, val, USBH_PRIV_UTMI_CTL_6368_REG);
}