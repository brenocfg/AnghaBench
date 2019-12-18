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
typedef  int /*<<< orphan*/  u32 ;
struct hdmi_hdcp_ctrl {scalar_t__ auth_retries; int /*<<< orphan*/  hdcp_state; struct hdmi* hdmi; } ;
struct hdmi {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDCP_STATE_AUTHENTICATED ; 
 int /*<<< orphan*/  HDMI_CTRL_ENCRYPTED ; 
 int /*<<< orphan*/  HDMI_DDC_ARBITRATION_HW_ARBITRATION ; 
 int /*<<< orphan*/  REG_HDMI_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_DDC_ARBITRATION ; 
 int /*<<< orphan*/  hdmi_read (struct hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void msm_hdmi_hdcp_auth_done(struct hdmi_hdcp_ctrl *hdcp_ctrl)
{
	struct hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg_val;
	unsigned long flags;

	/*
	 * Disable software DDC before going into part3 to make sure
	 * there is no Arbitration between software and hardware for DDC
	 */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_read(hdmi, REG_HDMI_DDC_ARBITRATION);
	reg_val |= HDMI_DDC_ARBITRATION_HW_ARBITRATION;
	hdmi_write(hdmi, REG_HDMI_DDC_ARBITRATION, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	/* enable HDMI Encrypt */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_read(hdmi, REG_HDMI_CTRL);
	reg_val |= HDMI_CTRL_ENCRYPTED;
	hdmi_write(hdmi, REG_HDMI_CTRL, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	hdcp_ctrl->hdcp_state = HDCP_STATE_AUTHENTICATED;
	hdcp_ctrl->auth_retries = 0;
}