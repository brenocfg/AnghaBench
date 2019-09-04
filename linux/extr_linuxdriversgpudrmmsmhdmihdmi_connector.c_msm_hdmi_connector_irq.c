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
struct hdmi_connector {int /*<<< orphan*/  hpd_work; struct hdmi* hdmi; } ;
struct hdmi {int /*<<< orphan*/  workq; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int HDMI_HPD_INT_CTRL_INT_ACK ; 
 int HDMI_HPD_INT_CTRL_INT_CONNECT ; 
 int HDMI_HPD_INT_CTRL_INT_EN ; 
 int HDMI_HPD_INT_STATUS_CABLE_DETECTED ; 
 int HDMI_HPD_INT_STATUS_INT ; 
 int /*<<< orphan*/  REG_HDMI_HPD_INT_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_HPD_INT_STATUS ; 
 int hdmi_read (struct hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hdmi_connector* to_hdmi_connector (struct drm_connector*) ; 

void msm_hdmi_connector_irq(struct drm_connector *connector)
{
	struct hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	struct hdmi *hdmi = hdmi_connector->hdmi;
	uint32_t hpd_int_status, hpd_int_ctrl;

	/* Process HPD: */
	hpd_int_status = hdmi_read(hdmi, REG_HDMI_HPD_INT_STATUS);
	hpd_int_ctrl   = hdmi_read(hdmi, REG_HDMI_HPD_INT_CTRL);

	if ((hpd_int_ctrl & HDMI_HPD_INT_CTRL_INT_EN) &&
			(hpd_int_status & HDMI_HPD_INT_STATUS_INT)) {
		bool detected = !!(hpd_int_status & HDMI_HPD_INT_STATUS_CABLE_DETECTED);

		/* ack & disable (temporarily) HPD events: */
		hdmi_write(hdmi, REG_HDMI_HPD_INT_CTRL,
			HDMI_HPD_INT_CTRL_INT_ACK);

		DBG("status=%04x, ctrl=%04x", hpd_int_status, hpd_int_ctrl);

		/* detect disconnect if we are connected or visa versa: */
		hpd_int_ctrl = HDMI_HPD_INT_CTRL_INT_EN;
		if (!detected)
			hpd_int_ctrl |= HDMI_HPD_INT_CTRL_INT_CONNECT;
		hdmi_write(hdmi, REG_HDMI_HPD_INT_CTRL, hpd_int_ctrl);

		queue_work(hdmi->workq, &hdmi_connector->hpd_work);
	}
}