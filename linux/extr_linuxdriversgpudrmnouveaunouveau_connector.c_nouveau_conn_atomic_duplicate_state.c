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
struct drm_connector_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ mask; } ;
struct nouveau_conn_atom {struct drm_connector_state state; TYPE_1__ set; int /*<<< orphan*/  procamp; int /*<<< orphan*/  scaler; int /*<<< orphan*/  dither; } ;
struct drm_connector {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_duplicate_state (struct drm_connector*,struct drm_connector_state*) ; 
 struct nouveau_conn_atom* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct nouveau_conn_atom* nouveau_conn_atom (int /*<<< orphan*/ ) ; 

struct drm_connector_state *
nouveau_conn_atomic_duplicate_state(struct drm_connector *connector)
{
	struct nouveau_conn_atom *armc = nouveau_conn_atom(connector->state);
	struct nouveau_conn_atom *asyc;
	if (!(asyc = kmalloc(sizeof(*asyc), GFP_KERNEL)))
		return NULL;
	__drm_atomic_helper_connector_duplicate_state(connector, &asyc->state);
	asyc->dither = armc->dither;
	asyc->scaler = armc->scaler;
	asyc->procamp = armc->procamp;
	asyc->set.mask = 0;
	return &asyc->state;
}