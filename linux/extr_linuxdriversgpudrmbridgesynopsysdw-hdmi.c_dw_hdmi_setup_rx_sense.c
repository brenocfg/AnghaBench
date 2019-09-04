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
struct dw_hdmi {int rxsense; int /*<<< orphan*/  mutex; int /*<<< orphan*/  force; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_hdmi_update_phy_mask (struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_update_power (struct dw_hdmi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dw_hdmi_setup_rx_sense(struct dw_hdmi *hdmi, bool hpd, bool rx_sense)
{
	mutex_lock(&hdmi->mutex);

	if (!hdmi->force) {
		/*
		 * If the RX sense status indicates we're disconnected,
		 * clear the software rxsense status.
		 */
		if (!rx_sense)
			hdmi->rxsense = false;

		/*
		 * Only set the software rxsense status when both
		 * rxsense and hpd indicates we're connected.
		 * This avoids what seems to be bad behaviour in
		 * at least iMX6S versions of the phy.
		 */
		if (hpd)
			hdmi->rxsense = true;

		dw_hdmi_update_power(hdmi);
		dw_hdmi_update_phy_mask(hdmi);
	}
	mutex_unlock(&hdmi->mutex);
}