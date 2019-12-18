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
struct hdmi_i2c_adapter {struct hdmi* hdmi; } ;
struct hdmi {int dummy; } ;

/* Variables and functions */
 int HDMI_DDC_CTRL_SOFT_RESET ; 
 int HDMI_DDC_CTRL_SW_STATUS_RESET ; 
 int HDMI_DDC_REF_REFTIMER (int) ; 
 int HDMI_DDC_REF_REFTIMER_ENABLE ; 
 int HDMI_DDC_SETUP_TIMEOUT (int) ; 
 int HDMI_DDC_SPEED_PRESCALE (int) ; 
 int HDMI_DDC_SPEED_THRESHOLD (int) ; 
 int /*<<< orphan*/  REG_HDMI_DDC_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_DDC_REF ; 
 int /*<<< orphan*/  REG_HDMI_DDC_SETUP ; 
 int /*<<< orphan*/  REG_HDMI_DDC_SPEED ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_ddc(struct hdmi_i2c_adapter *hdmi_i2c)
{
	struct hdmi *hdmi = hdmi_i2c->hdmi;

	hdmi_write(hdmi, REG_HDMI_DDC_CTRL,
			HDMI_DDC_CTRL_SW_STATUS_RESET);
	hdmi_write(hdmi, REG_HDMI_DDC_CTRL,
			HDMI_DDC_CTRL_SOFT_RESET);

	hdmi_write(hdmi, REG_HDMI_DDC_SPEED,
			HDMI_DDC_SPEED_THRESHOLD(2) |
			HDMI_DDC_SPEED_PRESCALE(10));

	hdmi_write(hdmi, REG_HDMI_DDC_SETUP,
			HDMI_DDC_SETUP_TIMEOUT(0xff));

	/* enable reference timer for 27us */
	hdmi_write(hdmi, REG_HDMI_DDC_REF,
			HDMI_DDC_REF_REFTIMER_ENABLE |
			HDMI_DDC_REF_REFTIMER(27));
}