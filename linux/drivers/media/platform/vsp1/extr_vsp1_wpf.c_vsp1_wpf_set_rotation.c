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
struct vsp1_video {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  config; } ;
struct TYPE_3__ {int rotate; } ;
struct vsp1_rwpf {TYPE_2__ entity; TYPE_1__ flip; struct vsp1_video* video; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  RWPF_PAD_SINK ; 
 int /*<<< orphan*/  RWPF_PAD_SOURCE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsp1_wpf_set_rotation(struct vsp1_rwpf *wpf, unsigned int rotation)
{
	struct vsp1_video *video = wpf->video;
	struct v4l2_mbus_framefmt *sink_format;
	struct v4l2_mbus_framefmt *source_format;
	bool rotate;
	int ret = 0;

	/*
	 * Only consider the 0°/180° from/to 90°/270° modifications, the rest
	 * is taken care of by the flipping configuration.
	 */
	rotate = rotation == 90 || rotation == 270;
	if (rotate == wpf->flip.rotate)
		return 0;

	/* Changing rotation isn't allowed when buffers are allocated. */
	mutex_lock(&video->lock);

	if (vb2_is_busy(&video->queue)) {
		ret = -EBUSY;
		goto done;
	}

	sink_format = vsp1_entity_get_pad_format(&wpf->entity,
						 wpf->entity.config,
						 RWPF_PAD_SINK);
	source_format = vsp1_entity_get_pad_format(&wpf->entity,
						   wpf->entity.config,
						   RWPF_PAD_SOURCE);

	mutex_lock(&wpf->entity.lock);

	if (rotate) {
		source_format->width = sink_format->height;
		source_format->height = sink_format->width;
	} else {
		source_format->width = sink_format->width;
		source_format->height = sink_format->height;
	}

	wpf->flip.rotate = rotate;

	mutex_unlock(&wpf->entity.lock);

done:
	mutex_unlock(&video->lock);
	return ret;
}