#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vsp1_pipeline {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct TYPE_12__ {TYPE_5__ handler; TYPE_4__* num_bins; TYPE_2__* max_rgb; } ;
struct vsp1_hgo {int num_bins; scalar_t__ max_rgb; TYPE_6__ ctrls; } ;
struct vsp1_entity {int /*<<< orphan*/  config; int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct v4l2_rect {unsigned int left; unsigned int top; unsigned int width; unsigned int height; } ;
struct TYPE_9__ {size_t val; } ;
struct TYPE_10__ {TYPE_3__ cur; } ;
struct TYPE_7__ {scalar_t__ val; } ;
struct TYPE_8__ {TYPE_1__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISTO_PAD_SINK ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_COMPOSE ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  VI6_HGO_MODE ; 
 unsigned int VI6_HGO_MODE_HRATIO_SHIFT ; 
 unsigned int VI6_HGO_MODE_MAXRGB ; 
 unsigned int VI6_HGO_MODE_STEP ; 
 unsigned int VI6_HGO_MODE_VRATIO_SHIFT ; 
 int /*<<< orphan*/  VI6_HGO_OFFSET ; 
 unsigned int VI6_HGO_OFFSET_HOFFSET_SHIFT ; 
 unsigned int VI6_HGO_OFFSET_VOFFSET_SHIFT ; 
 int /*<<< orphan*/  VI6_HGO_REGRST ; 
 unsigned int VI6_HGO_REGRST_RCLEA ; 
 int /*<<< orphan*/  VI6_HGO_SIZE ; 
 unsigned int VI6_HGO_SIZE_HSIZE_SHIFT ; 
 unsigned int VI6_HGO_SIZE_VSIZE_SHIFT ; 
 int* hgo_num_bins ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 struct vsp1_hgo* to_hgo (int /*<<< orphan*/ *) ; 
 struct v4l2_rect* vsp1_entity_get_pad_selection (struct vsp1_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_hgo_write (struct vsp1_hgo*,struct vsp1_dl_body*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hgo_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_list *dl,
				 struct vsp1_dl_body *dlb)
{
	struct vsp1_hgo *hgo = to_hgo(&entity->subdev);
	struct v4l2_rect *compose;
	struct v4l2_rect *crop;
	unsigned int hratio;
	unsigned int vratio;

	crop = vsp1_entity_get_pad_selection(entity, entity->config,
					     HISTO_PAD_SINK, V4L2_SEL_TGT_CROP);
	compose = vsp1_entity_get_pad_selection(entity, entity->config,
						HISTO_PAD_SINK,
						V4L2_SEL_TGT_COMPOSE);

	vsp1_hgo_write(hgo, dlb, VI6_HGO_REGRST, VI6_HGO_REGRST_RCLEA);

	vsp1_hgo_write(hgo, dlb, VI6_HGO_OFFSET,
		       (crop->left << VI6_HGO_OFFSET_HOFFSET_SHIFT) |
		       (crop->top << VI6_HGO_OFFSET_VOFFSET_SHIFT));
	vsp1_hgo_write(hgo, dlb, VI6_HGO_SIZE,
		       (crop->width << VI6_HGO_SIZE_HSIZE_SHIFT) |
		       (crop->height << VI6_HGO_SIZE_VSIZE_SHIFT));

	mutex_lock(hgo->ctrls.handler.lock);
	hgo->max_rgb = hgo->ctrls.max_rgb->cur.val;
	if (hgo->ctrls.num_bins)
		hgo->num_bins = hgo_num_bins[hgo->ctrls.num_bins->cur.val];
	mutex_unlock(hgo->ctrls.handler.lock);

	hratio = crop->width * 2 / compose->width / 3;
	vratio = crop->height * 2 / compose->height / 3;
	vsp1_hgo_write(hgo, dlb, VI6_HGO_MODE,
		       (hgo->num_bins == 256 ? VI6_HGO_MODE_STEP : 0) |
		       (hgo->max_rgb ? VI6_HGO_MODE_MAXRGB : 0) |
		       (hratio << VI6_HGO_MODE_HRATIO_SHIFT) |
		       (vratio << VI6_HGO_MODE_VRATIO_SHIFT));
}