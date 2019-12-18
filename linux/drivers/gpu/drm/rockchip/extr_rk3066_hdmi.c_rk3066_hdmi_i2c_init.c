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
struct rk3066_hdmi {int tmdsclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_DDC_BUS_FREQ_H ; 
 int /*<<< orphan*/  HDMI_DDC_BUS_FREQ_L ; 
 int HDMI_INTR_EDID_MASK ; 
 int /*<<< orphan*/  HDMI_INTR_MASK1 ; 
 int /*<<< orphan*/  HDMI_INTR_STATUS1 ; 
 int HDMI_SCL_RATE ; 
 int /*<<< orphan*/  hdmi_modb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rk3066_hdmi_i2c_init(struct rk3066_hdmi *hdmi)
{
	int ddc_bus_freq;

	ddc_bus_freq = (hdmi->tmdsclk >> 2) / HDMI_SCL_RATE;

	hdmi_writeb(hdmi, HDMI_DDC_BUS_FREQ_L, ddc_bus_freq & 0xFF);
	hdmi_writeb(hdmi, HDMI_DDC_BUS_FREQ_H, (ddc_bus_freq >> 8) & 0xFF);

	/* Clear the EDID interrupt flag and mute the interrupt. */
	hdmi_modb(hdmi, HDMI_INTR_MASK1, HDMI_INTR_EDID_MASK, 0);
	hdmi_writeb(hdmi, HDMI_INTR_STATUS1, HDMI_INTR_EDID_MASK);
}