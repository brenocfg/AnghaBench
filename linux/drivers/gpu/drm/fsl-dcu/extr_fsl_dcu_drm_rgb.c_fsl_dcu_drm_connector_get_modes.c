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
 int drm_panel_get_modes (int /*<<< orphan*/ ) ; 
 struct fsl_dcu_drm_connector* to_fsl_dcu_connector (struct drm_connector*) ; 

__attribute__((used)) static int fsl_dcu_drm_connector_get_modes(struct drm_connector *connector)
{
	struct fsl_dcu_drm_connector *fsl_connector;

	fsl_connector = to_fsl_dcu_connector(connector);
	return drm_panel_get_modes(fsl_connector->panel);
}