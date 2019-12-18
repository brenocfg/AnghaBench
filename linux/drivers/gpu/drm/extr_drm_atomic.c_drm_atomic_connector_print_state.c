#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_printer {int dummy; } ;
struct drm_connector_state {char* self_refresh_aware; TYPE_5__* writeback_job; TYPE_2__* crtc; struct drm_connector* connector; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct drm_connector {scalar_t__ connector_type; TYPE_6__* funcs; int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* atomic_print_state ) (struct drm_printer*,struct drm_connector_state const*) ;} ;
struct TYPE_11__ {TYPE_4__* fb; } ;
struct TYPE_9__ {char* id; } ;
struct TYPE_10__ {TYPE_3__ base; } ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_WRITEBACK ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct drm_printer*,struct drm_connector_state const*) ; 

__attribute__((used)) static void drm_atomic_connector_print_state(struct drm_printer *p,
		const struct drm_connector_state *state)
{
	struct drm_connector *connector = state->connector;

	drm_printf(p, "connector[%u]: %s\n", connector->base.id, connector->name);
	drm_printf(p, "\tcrtc=%s\n", state->crtc ? state->crtc->name : "(null)");
	drm_printf(p, "\tself_refresh_aware=%d\n", state->self_refresh_aware);

	if (connector->connector_type == DRM_MODE_CONNECTOR_WRITEBACK)
		if (state->writeback_job && state->writeback_job->fb)
			drm_printf(p, "\tfb=%d\n", state->writeback_job->fb->base.id);

	if (connector->funcs->atomic_print_state)
		connector->funcs->atomic_print_state(p, state);
}