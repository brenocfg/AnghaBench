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
typedef  unsigned int u16 ;
struct media_pad {unsigned int index; int /*<<< orphan*/  graph_obj; struct media_entity* entity; } ;
struct TYPE_2__ {struct media_device* mdev; } ;
struct media_entity {unsigned int num_pads; struct media_pad* pads; TYPE_1__ graph_obj; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;

/* Variables and functions */
 int E2BIG ; 
 unsigned int MEDIA_ENTITY_MAX_PADS ; 
 int /*<<< orphan*/  MEDIA_GRAPH_PAD ; 
 int /*<<< orphan*/  media_gobj_create (struct media_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int media_entity_pads_init(struct media_entity *entity, u16 num_pads,
			   struct media_pad *pads)
{
	struct media_device *mdev = entity->graph_obj.mdev;
	unsigned int i;

	if (num_pads >= MEDIA_ENTITY_MAX_PADS)
		return -E2BIG;

	entity->num_pads = num_pads;
	entity->pads = pads;

	if (mdev)
		mutex_lock(&mdev->graph_mutex);

	for (i = 0; i < num_pads; i++) {
		pads[i].entity = entity;
		pads[i].index = i;
		if (mdev)
			media_gobj_create(mdev, MEDIA_GRAPH_PAD,
					&entity->pads[i].graph_obj);
	}

	if (mdev)
		mutex_unlock(&mdev->graph_mutex);

	return 0;
}