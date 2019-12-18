#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct hdmi {TYPE_1__* pdev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HDMI_HPD_INT_STATUS_CABLE_DETECTED ; 
 int /*<<< orphan*/  REG_HDMI_HPD_INT_STATUS ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  enable_hpd_clocks (struct hdmi*,int) ; 
 int hdmi_read (struct hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum drm_connector_status detect_reg(struct hdmi *hdmi)
{
	uint32_t hpd_int_status;

	pm_runtime_get_sync(&hdmi->pdev->dev);
	enable_hpd_clocks(hdmi, true);

	hpd_int_status = hdmi_read(hdmi, REG_HDMI_HPD_INT_STATUS);

	enable_hpd_clocks(hdmi, false);
	pm_runtime_put_autosuspend(&hdmi->pdev->dev);

	return (hpd_int_status & HDMI_HPD_INT_STATUS_CABLE_DETECTED) ?
			connector_status_connected : connector_status_disconnected;
}