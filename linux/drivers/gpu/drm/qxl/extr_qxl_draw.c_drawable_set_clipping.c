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
struct qxl_rect {int dummy; } ;
struct qxl_device {int dummy; } ;
struct TYPE_2__ {int data_size; scalar_t__ data; scalar_t__ prev_chunk; scalar_t__ next_chunk; } ;
struct qxl_clip_rects {unsigned int num_rects; TYPE_1__ chunk; } ;
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int qxl_bo_kmap (struct qxl_bo*,void**) ; 

__attribute__((used)) static struct qxl_rect *drawable_set_clipping(struct qxl_device *qdev,
					      unsigned int num_clips,
					      struct qxl_bo *clips_bo)
{
	struct qxl_clip_rects *dev_clips;
	int ret;

	ret = qxl_bo_kmap(clips_bo, (void **)&dev_clips);
	if (ret) {
		return NULL;
	}
	dev_clips->num_rects = num_clips;
	dev_clips->chunk.next_chunk = 0;
	dev_clips->chunk.prev_chunk = 0;
	dev_clips->chunk.data_size = sizeof(struct qxl_rect) * num_clips;
	return (struct qxl_rect *)dev_clips->chunk.data;
}