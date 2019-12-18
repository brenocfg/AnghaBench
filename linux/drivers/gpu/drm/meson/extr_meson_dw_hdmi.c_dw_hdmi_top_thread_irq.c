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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct meson_dw_hdmi {int irq_stat; TYPE_1__ encoder; int /*<<< orphan*/  hdmi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HDMITX_TOP_INTR_HPD_FALL ; 
 int HDMITX_TOP_INTR_HPD_RISE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_hdmi_setup_rx_sense (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t dw_hdmi_top_thread_irq(int irq, void *dev_id)
{
	struct meson_dw_hdmi *dw_hdmi = dev_id;
	u32 stat = dw_hdmi->irq_stat;

	/* HPD Events */
	if (stat & (HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL)) {
		bool hpd_connected = false;

		if (stat & HDMITX_TOP_INTR_HPD_RISE)
			hpd_connected = true;

		dw_hdmi_setup_rx_sense(dw_hdmi->hdmi, hpd_connected,
				       hpd_connected);

		drm_helper_hpd_irq_event(dw_hdmi->encoder.dev);
	}

	return IRQ_HANDLED;
}