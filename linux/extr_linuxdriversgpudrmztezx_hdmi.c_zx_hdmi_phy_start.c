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
struct zx_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_writeb (struct zx_hdmi*,int,int) ; 

__attribute__((used)) static void zx_hdmi_phy_start(struct zx_hdmi *hdmi)
{
	/* Copy from ZTE BSP code */
	hdmi_writeb(hdmi, 0x222, 0x0);
	hdmi_writeb(hdmi, 0x224, 0x4);
	hdmi_writeb(hdmi, 0x909, 0x0);
	hdmi_writeb(hdmi, 0x7b0, 0x90);
	hdmi_writeb(hdmi, 0x7b1, 0x00);
	hdmi_writeb(hdmi, 0x7b2, 0xa7);
	hdmi_writeb(hdmi, 0x7b8, 0xaa);
	hdmi_writeb(hdmi, 0x7b2, 0xa7);
	hdmi_writeb(hdmi, 0x7b3, 0x0f);
	hdmi_writeb(hdmi, 0x7b4, 0x0f);
	hdmi_writeb(hdmi, 0x7b5, 0x55);
	hdmi_writeb(hdmi, 0x7b7, 0x03);
	hdmi_writeb(hdmi, 0x7b9, 0x12);
	hdmi_writeb(hdmi, 0x7ba, 0x32);
	hdmi_writeb(hdmi, 0x7bc, 0x68);
	hdmi_writeb(hdmi, 0x7be, 0x40);
	hdmi_writeb(hdmi, 0x7bf, 0x84);
	hdmi_writeb(hdmi, 0x7c1, 0x0f);
	hdmi_writeb(hdmi, 0x7c8, 0x02);
	hdmi_writeb(hdmi, 0x7c9, 0x03);
	hdmi_writeb(hdmi, 0x7ca, 0x40);
	hdmi_writeb(hdmi, 0x7dc, 0x31);
	hdmi_writeb(hdmi, 0x7e2, 0x04);
	hdmi_writeb(hdmi, 0x7e0, 0x06);
	hdmi_writeb(hdmi, 0x7cb, 0x68);
	hdmi_writeb(hdmi, 0x7f9, 0x02);
	hdmi_writeb(hdmi, 0x7b6, 0x02);
	hdmi_writeb(hdmi, 0x7f3, 0x0);
}