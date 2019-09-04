#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_panel_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 TYPE_1__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static void intel_dvo_destroy(struct drm_connector *connector)
{
	drm_connector_cleanup(connector);
	intel_panel_fini(&to_intel_connector(connector)->panel);
	kfree(connector);
}