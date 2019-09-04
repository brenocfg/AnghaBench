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
typedef  int uint32_t ;
struct hdmi_i2c_adapter {int sw_done; struct hdmi* hdmi; } ;
struct hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_DDC_INT_CTRL_SW_DONE_ACK ; 
 int HDMI_DDC_INT_CTRL_SW_DONE_INT ; 
 int HDMI_DDC_INT_CTRL_SW_DONE_MASK ; 
 int /*<<< orphan*/  REG_HDMI_DDC_INT_CTRL ; 
 int hdmi_read (struct hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sw_done(struct hdmi_i2c_adapter *hdmi_i2c)
{
	struct hdmi *hdmi = hdmi_i2c->hdmi;

	if (!hdmi_i2c->sw_done) {
		uint32_t ddc_int_ctrl;

		ddc_int_ctrl = hdmi_read(hdmi, REG_HDMI_DDC_INT_CTRL);

		if ((ddc_int_ctrl & HDMI_DDC_INT_CTRL_SW_DONE_MASK) &&
				(ddc_int_ctrl & HDMI_DDC_INT_CTRL_SW_DONE_INT)) {
			hdmi_i2c->sw_done = true;
			hdmi_write(hdmi, REG_HDMI_DDC_INT_CTRL,
					HDMI_DDC_INT_CTRL_SW_DONE_ACK);
		}
	}

	return hdmi_i2c->sw_done;
}