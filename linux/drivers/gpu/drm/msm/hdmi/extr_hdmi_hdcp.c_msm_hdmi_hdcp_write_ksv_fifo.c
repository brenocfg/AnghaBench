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
typedef  int u8 ;
typedef  int u32 ;
struct hdmi_hdcp_ctrl {int dev_count; int ksv_fifo_w_index; int* ksv_list; struct hdmi* hdmi; } ;
struct hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EAGAIN ; 
 int HDMI_HDCP_SHA_DATA_DONE ; 
 int HDMI_HDCP_SHA_STATUS_BLOCK_DONE ; 
 int HDMI_HDCP_SHA_STATUS_COMP_DONE ; 
 int REG_HDMI_HDCP_SHA_DATA ; 
 int /*<<< orphan*/  REG_HDMI_HDCP_SHA_STATUS ; 
 int hdmi_read (struct hdmi*,int /*<<< orphan*/ ) ; 
 int msm_hdmi_hdcp_scm_wr (struct hdmi_hdcp_ctrl*,int*,int*,int) ; 

__attribute__((used)) static int msm_hdmi_hdcp_write_ksv_fifo(struct hdmi_hdcp_ctrl *hdcp_ctrl)
{
	int i;
	struct hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 ksv_bytes, last_byte = 0;
	u8 *ksv_fifo = NULL;
	u32 reg_val, data, reg;
	u32 rc  = 0;

	ksv_bytes  = 5 * hdcp_ctrl->dev_count;

	/* Check if need to wait for HW completion */
	if (hdcp_ctrl->ksv_fifo_w_index) {
		reg_val = hdmi_read(hdmi, REG_HDMI_HDCP_SHA_STATUS);
		DBG("HDCP_SHA_STATUS=%08x", reg_val);
		if (hdcp_ctrl->ksv_fifo_w_index == ksv_bytes) {
			/* check COMP_DONE if last write */
			if (reg_val & HDMI_HDCP_SHA_STATUS_COMP_DONE) {
				DBG("COMP_DONE");
				return 0;
			} else {
				return -EAGAIN;
			}
		} else {
			/* check BLOCK_DONE if not last write */
			if (!(reg_val & HDMI_HDCP_SHA_STATUS_BLOCK_DONE))
				return -EAGAIN;

			DBG("BLOCK_DONE");
		}
	}

	ksv_bytes  -= hdcp_ctrl->ksv_fifo_w_index;
	if (ksv_bytes <= 64)
		last_byte = 1;
	else
		ksv_bytes = 64;

	ksv_fifo = hdcp_ctrl->ksv_list;
	ksv_fifo += hdcp_ctrl->ksv_fifo_w_index;

	for (i = 0; i < ksv_bytes; i++) {
		/* Write KSV byte and set DONE bit[0] for last byte*/
		reg_val = ksv_fifo[i] << 16;
		if ((i == (ksv_bytes - 1)) && last_byte)
			reg_val |= HDMI_HDCP_SHA_DATA_DONE;

		reg = REG_HDMI_HDCP_SHA_DATA;
		data = reg_val;
		rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, &reg, &data, 1);

		if (rc)
			return rc;
	}

	hdcp_ctrl->ksv_fifo_w_index += ksv_bytes;

	/*
	 *return -EAGAIN to notify caller to wait for COMP_DONE or BLOCK_DONE
	 */
	return -EAGAIN;
}