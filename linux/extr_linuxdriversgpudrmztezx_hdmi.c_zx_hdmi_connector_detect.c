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
struct zx_hdmi {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int TPI_HPD_CONNECTION ; 
 int /*<<< orphan*/  TPI_HPD_RSEN ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int hdmi_readb (struct zx_hdmi*,int /*<<< orphan*/ ) ; 
 struct zx_hdmi* to_zx_hdmi (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
zx_hdmi_connector_detect(struct drm_connector *connector, bool force)
{
	struct zx_hdmi *hdmi = to_zx_hdmi(connector);

	return (hdmi_readb(hdmi, TPI_HPD_RSEN) & TPI_HPD_CONNECTION) ?
		connector_status_connected : connector_status_disconnected;
}