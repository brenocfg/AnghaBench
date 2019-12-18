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
struct meson_dw_hdmi {int irq_stat; TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int (* top_read ) (struct meson_dw_hdmi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* top_write ) (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int HDMITX_TOP_INTR_HPD_FALL ; 
 int HDMITX_TOP_INTR_HPD_RISE ; 
 int /*<<< orphan*/  HDMITX_TOP_INTR_STAT ; 
 int /*<<< orphan*/  HDMITX_TOP_INTR_STAT_CLR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int stub1 (struct meson_dw_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t dw_hdmi_top_irq(int irq, void *dev_id)
{
	struct meson_dw_hdmi *dw_hdmi = dev_id;
	u32 stat;

	stat = dw_hdmi->data->top_read(dw_hdmi, HDMITX_TOP_INTR_STAT);
	dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_INTR_STAT_CLR, stat);

	/* HPD Events, handle in the threaded interrupt handler */
	if (stat & (HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL)) {
		dw_hdmi->irq_stat = stat;
		return IRQ_WAKE_THREAD;
	}

	/* HDMI Controller Interrupt */
	if (stat & 1)
		return IRQ_NONE;

	/* TOFIX Handle HDCP Interrupts */

	return IRQ_HANDLED;
}