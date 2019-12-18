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
typedef  int /*<<< orphan*/  u8 ;
struct dw_hdmi {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_FC_INVIDCONF ; 
 int /*<<< orphan*/  HDMI_MC_SWRSTZ ; 
 scalar_t__ HDMI_MC_SWRSTZ_TMDSSWRST_REQ ; 
 int /*<<< orphan*/  hdmi_readb (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_hdmi_clear_overflow(struct dw_hdmi *hdmi)
{
	unsigned int count;
	unsigned int i;
	u8 val;

	/*
	 * Under some circumstances the Frame Composer arithmetic unit can miss
	 * an FC register write due to being busy processing the previous one.
	 * The issue can be worked around by issuing a TMDS software reset and
	 * then write one of the FC registers several times.
	 *
	 * The number of iterations matters and depends on the HDMI TX revision
	 * (and possibly on the platform). So far i.MX6Q (v1.30a), i.MX6DL
	 * (v1.31a) and multiple Allwinner SoCs (v1.32a) have been identified
	 * as needing the workaround, with 4 iterations for v1.30a and 1
	 * iteration for others.
	 * The Amlogic Meson GX SoCs (v2.01a) have been identified as needing
	 * the workaround with a single iteration.
	 * The Rockchip RK3288 SoC (v2.00a) and RK3328/RK3399 SoCs (v2.11a) have
	 * been identified as needing the workaround with a single iteration.
	 */

	switch (hdmi->version) {
	case 0x130a:
		count = 4;
		break;
	case 0x131a:
	case 0x132a:
	case 0x200a:
	case 0x201a:
	case 0x211a:
	case 0x212a:
		count = 1;
		break;
	default:
		return;
	}

	/* TMDS software reset */
	hdmi_writeb(hdmi, (u8)~HDMI_MC_SWRSTZ_TMDSSWRST_REQ, HDMI_MC_SWRSTZ);

	val = hdmi_readb(hdmi, HDMI_FC_INVIDCONF);
	for (i = 0; i < count; i++)
		hdmi_writeb(hdmi, val, HDMI_FC_INVIDCONF);
}