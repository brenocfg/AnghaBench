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
struct nvkm_object {TYPE_1__* client; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  objroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nvkm_object_remove(struct nvkm_object *object)
{
	if (!RB_EMPTY_NODE(&object->node))
		rb_erase(&object->node, &object->client->objroot);
}