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
struct TYPE_2__ {int /*<<< orphan*/  oclass; } ;
struct nvkm_oclass {int /*<<< orphan*/  object; int /*<<< orphan*/  token; int /*<<< orphan*/  route; int /*<<< orphan*/  handle; TYPE_1__ base; int /*<<< orphan*/  engine; int /*<<< orphan*/  client; } ;
struct nvkm_object_func {int dummy; } ;
struct nvkm_object {int /*<<< orphan*/  engine; int /*<<< orphan*/  node; int /*<<< orphan*/  tree; int /*<<< orphan*/  head; int /*<<< orphan*/  object; int /*<<< orphan*/  token; int /*<<< orphan*/  route; int /*<<< orphan*/  handle; int /*<<< orphan*/  oclass; int /*<<< orphan*/  client; struct nvkm_object_func const* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_engine_ref (int /*<<< orphan*/ ) ; 

void
nvkm_object_ctor(const struct nvkm_object_func *func,
		 const struct nvkm_oclass *oclass, struct nvkm_object *object)
{
	object->func = func;
	object->client = oclass->client;
	object->engine = nvkm_engine_ref(oclass->engine);
	object->oclass = oclass->base.oclass;
	object->handle = oclass->handle;
	object->route  = oclass->route;
	object->token  = oclass->token;
	object->object = oclass->object;
	INIT_LIST_HEAD(&object->head);
	INIT_LIST_HEAD(&object->tree);
	RB_CLEAR_NODE(&object->node);
	WARN_ON(IS_ERR(object->engine));
}