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
struct inno_hdmi {int tmds_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_BUS_FREQ_H ; 
 int /*<<< orphan*/  DDC_BUS_FREQ_L ; 
 int /*<<< orphan*/  HDMI_INTERRUPT_MASK1 ; 
 int /*<<< orphan*/  HDMI_INTERRUPT_STATUS1 ; 
 int HDMI_SCL_RATE ; 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,int /*<<< orphan*/ ,int) ; 
 int m_INT_EDID_READY ; 

__attribute__((used)) static void inno_hdmi_i2c_init(struct inno_hdmi *hdmi)
{
	int ddc_bus_freq;

	ddc_bus_freq = (hdmi->tmds_rate >> 2) / HDMI_SCL_RATE;

	hdmi_writeb(hdmi, DDC_BUS_FREQ_L, ddc_bus_freq & 0xFF);
	hdmi_writeb(hdmi, DDC_BUS_FREQ_H, (ddc_bus_freq >> 8) & 0xFF);

	/* Clear the EDID interrupt flag and mute the interrupt */
	hdmi_writeb(hdmi, HDMI_INTERRUPT_MASK1, 0);
	hdmi_writeb(hdmi, HDMI_INTERRUPT_STATUS1, m_INT_EDID_READY);
}