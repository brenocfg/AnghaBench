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
struct qxl_output {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 struct qxl_output* drm_connector_to_qxl_output (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct qxl_output*) ; 

__attribute__((used)) static void qxl_conn_destroy(struct drm_connector *connector)
{
	struct qxl_output *qxl_output =
		drm_connector_to_qxl_output(connector);

	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	kfree(qxl_output);
}