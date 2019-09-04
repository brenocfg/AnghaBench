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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct hdmi_wp_data {int dummy; } ;
struct omap_hdmi {TYPE_1__ core; struct hdmi_wp_data wp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CORE_SYS_INTR4 ; 
 int HDMI_IRQ_CORE ; 
 int HDMI_IRQ_LINK_CONNECT ; 
 int HDMI_IRQ_LINK_DISCONNECT ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_LDOON ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_OFF ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_TXON ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hdmi4_cec_irq (TYPE_1__*) ; 
 int hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdmi_wp_get_irqstatus (struct hdmi_wp_data*) ; 
 int /*<<< orphan*/  hdmi_wp_set_irqstatus (struct hdmi_wp_data*,int) ; 
 int /*<<< orphan*/  hdmi_wp_set_phy_pwr (struct hdmi_wp_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t hdmi_irq_handler(int irq, void *data)
{
	struct omap_hdmi *hdmi = data;
	struct hdmi_wp_data *wp = &hdmi->wp;
	u32 irqstatus;

	irqstatus = hdmi_wp_get_irqstatus(wp);
	hdmi_wp_set_irqstatus(wp, irqstatus);

	if ((irqstatus & HDMI_IRQ_LINK_CONNECT) &&
			irqstatus & HDMI_IRQ_LINK_DISCONNECT) {
		/*
		 * If we get both connect and disconnect interrupts at the same
		 * time, turn off the PHY, clear interrupts, and restart, which
		 * raises connect interrupt if a cable is connected, or nothing
		 * if cable is not connected.
		 */
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_OFF);

		hdmi_wp_set_irqstatus(wp, HDMI_IRQ_LINK_CONNECT |
				HDMI_IRQ_LINK_DISCONNECT);

		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	} else if (irqstatus & HDMI_IRQ_LINK_CONNECT) {
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_TXON);
	} else if (irqstatus & HDMI_IRQ_LINK_DISCONNECT) {
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	}
	if (irqstatus & HDMI_IRQ_CORE) {
		u32 intr4 = hdmi_read_reg(hdmi->core.base, HDMI_CORE_SYS_INTR4);

		hdmi_write_reg(hdmi->core.base, HDMI_CORE_SYS_INTR4, intr4);
		if (intr4 & 8)
			hdmi4_cec_irq(&hdmi->core);
	}

	return IRQ_HANDLED;
}