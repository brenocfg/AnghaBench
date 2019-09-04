#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct intel_sdvo_connector_state {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct intel_sdvo_connector {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct intel_sdvo_connector*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_sdvo_connector *intel_sdvo_connector_alloc(void)
{
	struct intel_sdvo_connector *sdvo_connector;
	struct intel_sdvo_connector_state *conn_state;

	sdvo_connector = kzalloc(sizeof(*sdvo_connector), GFP_KERNEL);
	if (!sdvo_connector)
		return NULL;

	conn_state = kzalloc(sizeof(*conn_state), GFP_KERNEL);
	if (!conn_state) {
		kfree(sdvo_connector);
		return NULL;
	}

	__drm_atomic_helper_connector_reset(&sdvo_connector->base.base,
					    &conn_state->base.base);

	return sdvo_connector;
}