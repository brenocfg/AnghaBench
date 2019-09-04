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
typedef  scalar_t__ uint32_t ;
struct vmw_private {int dummy; } ;
struct vmw_display_unit {scalar_t__ unit; scalar_t__ pref_active; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_REG_NUM_DISPLAYS ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct vmw_display_unit* vmw_connector_to_du (struct drm_connector*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 scalar_t__ vmw_read (struct vmw_private*,int /*<<< orphan*/ ) ; 

enum drm_connector_status
vmw_du_connector_detect(struct drm_connector *connector, bool force)
{
	uint32_t num_displays;
	struct drm_device *dev = connector->dev;
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_display_unit *du = vmw_connector_to_du(connector);

	num_displays = vmw_read(dev_priv, SVGA_REG_NUM_DISPLAYS);

	return ((vmw_connector_to_du(connector)->unit < num_displays &&
		 du->pref_active) ?
		connector_status_connected : connector_status_disconnected);
}