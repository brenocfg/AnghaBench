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
struct nouveau_conn_atom {int /*<<< orphan*/  state; } ;
struct drm_connector_state {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_connector_destroy_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nouveau_conn_atom*) ; 
 struct nouveau_conn_atom* nouveau_conn_atom (struct drm_connector_state*) ; 

void
nouveau_conn_atomic_destroy_state(struct drm_connector *connector,
				  struct drm_connector_state *state)
{
	struct nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	__drm_atomic_helper_connector_destroy_state(&asyc->state);
	kfree(asyc);
}