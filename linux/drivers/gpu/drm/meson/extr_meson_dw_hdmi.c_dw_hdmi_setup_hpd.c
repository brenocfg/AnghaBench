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
struct meson_dw_hdmi {TYPE_1__* data; } ;
struct dw_hdmi {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* top_write ) (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HDMITX_TOP_HPD_FILTER ; 
 int HDMITX_TOP_INTR_HPD_FALL ; 
 int HDMITX_TOP_INTR_HPD_RISE ; 
 int /*<<< orphan*/  HDMITX_TOP_INTR_MASKN ; 
 int /*<<< orphan*/  HDMITX_TOP_INTR_STAT_CLR ; 
 int /*<<< orphan*/  dw_hdmi_top_write_bits (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct meson_dw_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_hdmi_setup_hpd(struct dw_hdmi *hdmi,
			      void *data)
{
	struct meson_dw_hdmi *dw_hdmi = (struct meson_dw_hdmi *)data;

	/* Setup HPD Filter */
	dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_HPD_FILTER,
			  (0xa << 12) | 0xa0);

	/* Clear interrupts */
	dw_hdmi->data->top_write(dw_hdmi, HDMITX_TOP_INTR_STAT_CLR,
			  HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL);

	/* Unmask interrupts */
	dw_hdmi_top_write_bits(dw_hdmi, HDMITX_TOP_INTR_MASKN,
			HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL,
			HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL);
}