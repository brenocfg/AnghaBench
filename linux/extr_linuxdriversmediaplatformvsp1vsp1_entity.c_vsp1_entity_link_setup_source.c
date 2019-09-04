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
struct vsp1_entity {scalar_t__ type; scalar_t__ sink_pad; struct vsp1_entity* sink; int /*<<< orphan*/  route; } ;
struct media_pad {scalar_t__ index; int /*<<< orphan*/  entity; } ;

/* Variables and functions */
 int EBUSY ; 
 int MEDIA_LNK_FL_ENABLED ; 
 scalar_t__ VSP1_ENTITY_HGO ; 
 scalar_t__ VSP1_ENTITY_HGT ; 
 struct vsp1_entity* media_entity_to_vsp1_entity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsp1_entity_link_setup_source(const struct media_pad *source_pad,
					 const struct media_pad *sink_pad,
					 u32 flags)
{
	struct vsp1_entity *source;

	source = media_entity_to_vsp1_entity(source_pad->entity);

	if (!source->route)
		return 0;

	if (flags & MEDIA_LNK_FL_ENABLED) {
		struct vsp1_entity *sink
			= media_entity_to_vsp1_entity(sink_pad->entity);

		/*
		 * Fan-out is limited to one for the normal data path plus
		 * optional HGO and HGT. We ignore the HGO and HGT here.
		 */
		if (sink->type != VSP1_ENTITY_HGO &&
		    sink->type != VSP1_ENTITY_HGT) {
			if (source->sink)
				return -EBUSY;
			source->sink = sink;
			source->sink_pad = sink_pad->index;
		}
	} else {
		source->sink = NULL;
		source->sink_pad = 0;
	}

	return 0;
}