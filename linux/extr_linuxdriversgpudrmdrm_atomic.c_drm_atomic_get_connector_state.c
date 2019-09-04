#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_config {int /*<<< orphan*/  num_connector; int /*<<< orphan*/  connection_mutex; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {scalar_t__ crtc; struct drm_atomic_state* state; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_3__ base; int /*<<< orphan*/  state; TYPE_2__* funcs; TYPE_1__* dev; } ;
struct drm_atomic_state {int num_connector; struct __drm_connnectors_state* connectors; int /*<<< orphan*/  acquire_ctx; } ;
struct __drm_connnectors_state {struct drm_connector* ptr; struct drm_connector_state* new_state; int /*<<< orphan*/  old_state; struct drm_connector_state* state; } ;
struct TYPE_5__ {struct drm_connector_state* (* atomic_duplicate_state ) (struct drm_connector*) ;} ;
struct TYPE_4__ {struct drm_mode_config mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_connector_state*,struct drm_atomic_state*) ; 
 int ENOMEM ; 
 struct drm_connector_state* ERR_CAST (struct drm_crtc_state*) ; 
 struct drm_connector_state* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (struct drm_atomic_state*,scalar_t__) ; 
 int /*<<< orphan*/  drm_connector_get (struct drm_connector*) ; 
 int drm_connector_index (struct drm_connector*) ; 
 int drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct __drm_connnectors_state* krealloc (struct __drm_connnectors_state*,int,int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct __drm_connnectors_state*,int /*<<< orphan*/ ,int) ; 
 struct drm_connector_state* stub1 (struct drm_connector*) ; 

struct drm_connector_state *
drm_atomic_get_connector_state(struct drm_atomic_state *state,
			  struct drm_connector *connector)
{
	int ret, index;
	struct drm_mode_config *config = &connector->dev->mode_config;
	struct drm_connector_state *connector_state;

	WARN_ON(!state->acquire_ctx);

	ret = drm_modeset_lock(&config->connection_mutex, state->acquire_ctx);
	if (ret)
		return ERR_PTR(ret);

	index = drm_connector_index(connector);

	if (index >= state->num_connector) {
		struct __drm_connnectors_state *c;
		int alloc = max(index + 1, config->num_connector);

		c = krealloc(state->connectors, alloc * sizeof(*state->connectors), GFP_KERNEL);
		if (!c)
			return ERR_PTR(-ENOMEM);

		state->connectors = c;
		memset(&state->connectors[state->num_connector], 0,
		       sizeof(*state->connectors) * (alloc - state->num_connector));

		state->num_connector = alloc;
	}

	if (state->connectors[index].state)
		return state->connectors[index].state;

	connector_state = connector->funcs->atomic_duplicate_state(connector);
	if (!connector_state)
		return ERR_PTR(-ENOMEM);

	drm_connector_get(connector);
	state->connectors[index].state = connector_state;
	state->connectors[index].old_state = connector->state;
	state->connectors[index].new_state = connector_state;
	state->connectors[index].ptr = connector;
	connector_state->state = state;

	DRM_DEBUG_ATOMIC("Added [CONNECTOR:%d:%s] %p state to %p\n",
			 connector->base.id, connector->name,
			 connector_state, state);

	if (connector_state->crtc) {
		struct drm_crtc_state *crtc_state;

		crtc_state = drm_atomic_get_crtc_state(state,
						       connector_state->crtc);
		if (IS_ERR(crtc_state))
			return ERR_CAST(crtc_state);
	}

	return connector_state;
}