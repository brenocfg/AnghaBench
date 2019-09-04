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
struct dw_hdmi {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int HDMI_PHY_HPD ; 
 int /*<<< orphan*/  HDMI_PHY_STAT0 ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int hdmi_readb (struct dw_hdmi*,int /*<<< orphan*/ ) ; 

enum drm_connector_status dw_hdmi_phy_read_hpd(struct dw_hdmi *hdmi,
					       void *data)
{
	return hdmi_readb(hdmi, HDMI_PHY_STAT0) & HDMI_PHY_HPD ?
		connector_status_connected : connector_status_disconnected;
}