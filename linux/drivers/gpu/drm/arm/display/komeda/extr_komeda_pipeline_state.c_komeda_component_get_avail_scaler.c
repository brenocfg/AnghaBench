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
typedef  int u32 ;
struct komeda_scaler {int dummy; } ;
struct komeda_pipeline_state {int active_comps; } ;
struct komeda_component {int /*<<< orphan*/  pipeline; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int KOMEDA_PIPELINE_SCALERS ; 
 struct komeda_component* komeda_component_pickup_output (struct komeda_component*,int) ; 
 struct komeda_pipeline_state* komeda_pipeline_get_state (int /*<<< orphan*/ ,struct drm_atomic_state*) ; 
 struct komeda_scaler* to_scaler (struct komeda_component*) ; 

__attribute__((used)) static struct komeda_scaler *
komeda_component_get_avail_scaler(struct komeda_component *c,
				  struct drm_atomic_state *state)
{
	struct komeda_pipeline_state *pipe_st;
	u32 avail_scalers;

	pipe_st = komeda_pipeline_get_state(c->pipeline, state);
	if (!pipe_st)
		return NULL;

	avail_scalers = (pipe_st->active_comps & KOMEDA_PIPELINE_SCALERS) ^
			KOMEDA_PIPELINE_SCALERS;

	c = komeda_component_pickup_output(c, avail_scalers);

	return to_scaler(c);
}