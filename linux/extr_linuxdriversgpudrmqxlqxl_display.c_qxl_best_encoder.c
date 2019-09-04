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
struct drm_encoder {int dummy; } ;
struct qxl_output {struct drm_encoder enc; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 struct qxl_output* drm_connector_to_qxl_output (struct drm_connector*) ; 

__attribute__((used)) static struct drm_encoder *qxl_best_encoder(struct drm_connector *connector)
{
	struct qxl_output *qxl_output =
		drm_connector_to_qxl_output(connector);

	DRM_DEBUG("\n");
	return &qxl_output->enc;
}