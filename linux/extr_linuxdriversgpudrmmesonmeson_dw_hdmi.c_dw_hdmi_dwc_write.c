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
struct meson_dw_hdmi {scalar_t__ hdmitx; } ;

/* Variables and functions */
 scalar_t__ HDMITX_DWC_ADDR_REG ; 
 scalar_t__ HDMITX_DWC_DATA_REG ; 
 int /*<<< orphan*/  reg_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void dw_hdmi_dwc_write(struct meson_dw_hdmi *dw_hdmi,
				     unsigned int addr, unsigned int data)
{
	unsigned long flags;

	spin_lock_irqsave(&reg_lock, flags);

	/* ADDR must be written twice */
	writel(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDR_REG);
	writel(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDR_REG);

	/* Write needs single DATA write */
	writel(data, dw_hdmi->hdmitx + HDMITX_DWC_DATA_REG);

	spin_unlock_irqrestore(&reg_lock, flags);
}