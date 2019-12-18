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
typedef  int u32 ;
struct hdmi_hdcp_ctrl {int dummy; } ;

/* Variables and functions */
 int HDCP_REG_DISABLE ; 
 int HDCP_REG_ENABLE ; 
 int REG_HDMI_HDCP_SHA_CTRL ; 
 int msm_hdmi_hdcp_scm_wr (struct hdmi_hdcp_ctrl*,int*,int*,int) ; 

__attribute__((used)) static int msm_hdmi_hdcp_reset_sha_engine(struct hdmi_hdcp_ctrl *hdcp_ctrl)
{
	u32 reg[2], data[2];
	u32 rc  = 0;

	reg[0] = REG_HDMI_HDCP_SHA_CTRL;
	data[0] = HDCP_REG_ENABLE;
	reg[1] = REG_HDMI_HDCP_SHA_CTRL;
	data[1] = HDCP_REG_DISABLE;

	rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, reg, data, 2);

	return rc;
}