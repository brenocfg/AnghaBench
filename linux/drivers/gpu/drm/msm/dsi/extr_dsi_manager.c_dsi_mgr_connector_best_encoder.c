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
struct msm_dsi {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int dsi_mgr_connector_get_id (struct drm_connector*) ; 
 struct msm_dsi* dsi_mgr_get_dsi (int) ; 
 struct drm_encoder* msm_dsi_get_encoder (struct msm_dsi*) ; 

__attribute__((used)) static struct drm_encoder *
dsi_mgr_connector_best_encoder(struct drm_connector *connector)
{
	int id = dsi_mgr_connector_get_id(connector);
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);

	DBG("");
	return msm_dsi_get_encoder(msm_dsi);
}