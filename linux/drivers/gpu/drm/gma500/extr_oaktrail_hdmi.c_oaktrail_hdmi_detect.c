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
struct oaktrail_hdmi_dev {int dummy; } ;
struct drm_psb_private {struct oaktrail_hdmi_dev* hdmi_priv; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int HDMI_DETECT_HDP ; 
 int /*<<< orphan*/  HDMI_HSR ; 
 int HDMI_READ (int /*<<< orphan*/ ) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 

__attribute__((used)) static enum drm_connector_status
oaktrail_hdmi_detect(struct drm_connector *connector, bool force)
{
	enum drm_connector_status status;
	struct drm_device *dev = connector->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_hdmi_dev *hdmi_dev = dev_priv->hdmi_priv;
	u32 temp;

	temp = HDMI_READ(HDMI_HSR);
	DRM_DEBUG_KMS("HDMI_HSR %x\n", temp);

	if ((temp & HDMI_DETECT_HDP) != 0)
		status = connector_status_connected;
	else
		status = connector_status_disconnected;

	return status;
}