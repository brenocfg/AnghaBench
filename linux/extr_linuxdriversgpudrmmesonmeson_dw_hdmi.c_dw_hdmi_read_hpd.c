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
struct meson_dw_hdmi {int dummy; } ;
struct dw_hdmi {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  HDMITX_TOP_STAT0 ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  dw_hdmi_top_read (struct meson_dw_hdmi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_connector_status dw_hdmi_read_hpd(struct dw_hdmi *hdmi,
			     void *data)
{
	struct meson_dw_hdmi *dw_hdmi = (struct meson_dw_hdmi *)data;

	return !!dw_hdmi_top_read(dw_hdmi, HDMITX_TOP_STAT0) ?
		connector_status_connected : connector_status_disconnected;
}