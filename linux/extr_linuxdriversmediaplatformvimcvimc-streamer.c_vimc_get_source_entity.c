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
struct media_pad {struct media_entity* entity; } ;
struct media_entity {int num_pads; TYPE_1__* pads; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MEDIA_PAD_FL_SOURCE ; 
 struct media_pad* media_entity_remote_pad (TYPE_1__*) ; 

__attribute__((used)) static struct media_entity *vimc_get_source_entity(struct media_entity *ent)
{
	struct media_pad *pad;
	int i;

	for (i = 0; i < ent->num_pads; i++) {
		if (ent->pads[i].flags & MEDIA_PAD_FL_SOURCE)
			continue;
		pad = media_entity_remote_pad(&ent->pads[i]);
		return pad ? pad->entity : NULL;
	}
	return NULL;
}