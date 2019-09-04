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
struct hdmi {int /*<<< orphan*/  pdev; scalar_t__ i2c; int /*<<< orphan*/ * phy_dev; int /*<<< orphan*/ * phy; scalar_t__ workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  msm_hdmi_hdcp_destroy (struct hdmi*) ; 
 int /*<<< orphan*/  msm_hdmi_i2c_destroy (scalar_t__) ; 
 int /*<<< orphan*/  platform_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msm_hdmi_destroy(struct hdmi *hdmi)
{
	/*
	 * at this point, hpd has been disabled,
	 * after flush workq, it's safe to deinit hdcp
	 */
	if (hdmi->workq) {
		flush_workqueue(hdmi->workq);
		destroy_workqueue(hdmi->workq);
	}
	msm_hdmi_hdcp_destroy(hdmi);

	if (hdmi->phy_dev) {
		put_device(hdmi->phy_dev);
		hdmi->phy = NULL;
		hdmi->phy_dev = NULL;
	}

	if (hdmi->i2c)
		msm_hdmi_i2c_destroy(hdmi->i2c);

	platform_set_drvdata(hdmi->pdev, NULL);
}