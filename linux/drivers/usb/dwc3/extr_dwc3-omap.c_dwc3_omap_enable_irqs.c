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
struct dwc3_omap {int dummy; } ;

/* Variables and functions */
 int USBOTGSS_IRQMISC_CHRGVBUS_FALL ; 
 int USBOTGSS_IRQMISC_CHRGVBUS_RISE ; 
 int USBOTGSS_IRQMISC_DISCHRGVBUS_FALL ; 
 int USBOTGSS_IRQMISC_DISCHRGVBUS_RISE ; 
 int USBOTGSS_IRQMISC_DRVVBUS_FALL ; 
 int USBOTGSS_IRQMISC_DRVVBUS_RISE ; 
 int USBOTGSS_IRQMISC_IDPULLUP_FALL ; 
 int USBOTGSS_IRQMISC_IDPULLUP_RISE ; 
 int USBOTGSS_IRQMISC_OEVT ; 
 int USBOTGSS_IRQO_COREIRQ_ST ; 
 int /*<<< orphan*/  dwc3_omap_write_irq0_set (struct dwc3_omap*,int) ; 
 int /*<<< orphan*/  dwc3_omap_write_irqmisc_set (struct dwc3_omap*,int) ; 

__attribute__((used)) static void dwc3_omap_enable_irqs(struct dwc3_omap *omap)
{
	u32			reg;

	/* enable all IRQs */
	reg = USBOTGSS_IRQO_COREIRQ_ST;
	dwc3_omap_write_irq0_set(omap, reg);

	reg = (USBOTGSS_IRQMISC_OEVT |
			USBOTGSS_IRQMISC_DRVVBUS_RISE |
			USBOTGSS_IRQMISC_CHRGVBUS_RISE |
			USBOTGSS_IRQMISC_DISCHRGVBUS_RISE |
			USBOTGSS_IRQMISC_IDPULLUP_RISE |
			USBOTGSS_IRQMISC_DRVVBUS_FALL |
			USBOTGSS_IRQMISC_CHRGVBUS_FALL |
			USBOTGSS_IRQMISC_DISCHRGVBUS_FALL |
			USBOTGSS_IRQMISC_IDPULLUP_FALL);

	dwc3_omap_write_irqmisc_set(omap, reg);
}