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
struct fsl_dcu_drm_connector {int /*<<< orphan*/  panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_panel_detach (int /*<<< orphan*/ ) ; 
 struct fsl_dcu_drm_connector* to_fsl_dcu_connector (struct drm_connector*) ; 

__attribute__((used)) static void fsl_dcu_drm_connector_destroy(struct drm_connector *connector)
{
	struct fsl_dcu_drm_connector *fsl_con = to_fsl_dcu_connector(connector);

	drm_connector_unregister(connector);
	drm_panel_detach(fsl_con->panel);
	drm_connector_cleanup(connector);
}