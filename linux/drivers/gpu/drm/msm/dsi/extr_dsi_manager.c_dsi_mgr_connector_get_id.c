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
struct dsi_connector {int id; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct dsi_connector* to_dsi_connector (struct drm_connector*) ; 

__attribute__((used)) static inline int dsi_mgr_connector_get_id(struct drm_connector *connector)
{
	struct dsi_connector *dsi_connector = to_dsi_connector(connector);
	return dsi_connector->id;
}