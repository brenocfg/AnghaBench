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
typedef  unsigned int u8 ;
struct vsp1_pipeline {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct vsp1_hgt {unsigned int* hue_areas; TYPE_1__ ctrls; } ;
struct vsp1_entity {int /*<<< orphan*/  config; int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;
struct v4l2_rect {unsigned int left; unsigned int top; unsigned int width; unsigned int height; } ;

/* Variables and functions */
 unsigned int HGT_NUM_HUE_AREAS ; 
 int /*<<< orphan*/  HISTO_PAD_SINK ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_COMPOSE ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  VI6_HGT_HUE_AREA (unsigned int) ; 
 unsigned int VI6_HGT_HUE_AREA_LOWER_SHIFT ; 
 unsigned int VI6_HGT_HUE_AREA_UPPER_SHIFT ; 
 int /*<<< orphan*/  VI6_HGT_MODE ; 
 unsigned int VI6_HGT_MODE_HRATIO_SHIFT ; 
 unsigned int VI6_HGT_MODE_VRATIO_SHIFT ; 
 int /*<<< orphan*/  VI6_HGT_OFFSET ; 
 unsigned int VI6_HGT_OFFSET_HOFFSET_SHIFT ; 
 unsigned int VI6_HGT_OFFSET_VOFFSET_SHIFT ; 
 int /*<<< orphan*/  VI6_HGT_REGRST ; 
 unsigned int VI6_HGT_REGRST_RCLEA ; 
 int /*<<< orphan*/  VI6_HGT_SIZE ; 
 unsigned int VI6_HGT_SIZE_HSIZE_SHIFT ; 
 unsigned int VI6_HGT_SIZE_VSIZE_SHIFT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 struct vsp1_hgt* to_hgt (int /*<<< orphan*/ *) ; 
 struct v4l2_rect* vsp1_entity_get_pad_selection (struct vsp1_entity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_hgt_write (struct vsp1_hgt*,struct vsp1_dl_body*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hgt_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_list *dl,
				 struct vsp1_dl_body *dlb)
{
	struct vsp1_hgt *hgt = to_hgt(&entity->subdev);
	struct v4l2_rect *compose;
	struct v4l2_rect *crop;
	unsigned int hratio;
	unsigned int vratio;
	u8 lower;
	u8 upper;
	unsigned int i;

	crop = vsp1_entity_get_pad_selection(entity, entity->config,
					     HISTO_PAD_SINK, V4L2_SEL_TGT_CROP);
	compose = vsp1_entity_get_pad_selection(entity, entity->config,
						HISTO_PAD_SINK,
						V4L2_SEL_TGT_COMPOSE);

	vsp1_hgt_write(hgt, dlb, VI6_HGT_REGRST, VI6_HGT_REGRST_RCLEA);

	vsp1_hgt_write(hgt, dlb, VI6_HGT_OFFSET,
		       (crop->left << VI6_HGT_OFFSET_HOFFSET_SHIFT) |
		       (crop->top << VI6_HGT_OFFSET_VOFFSET_SHIFT));
	vsp1_hgt_write(hgt, dlb, VI6_HGT_SIZE,
		       (crop->width << VI6_HGT_SIZE_HSIZE_SHIFT) |
		       (crop->height << VI6_HGT_SIZE_VSIZE_SHIFT));

	mutex_lock(hgt->ctrls.lock);
	for (i = 0; i < HGT_NUM_HUE_AREAS; ++i) {
		lower = hgt->hue_areas[i*2 + 0];
		upper = hgt->hue_areas[i*2 + 1];
		vsp1_hgt_write(hgt, dlb, VI6_HGT_HUE_AREA(i),
			       (lower << VI6_HGT_HUE_AREA_LOWER_SHIFT) |
			       (upper << VI6_HGT_HUE_AREA_UPPER_SHIFT));
	}
	mutex_unlock(hgt->ctrls.lock);

	hratio = crop->width * 2 / compose->width / 3;
	vratio = crop->height * 2 / compose->height / 3;
	vsp1_hgt_write(hgt, dlb, VI6_HGT_MODE,
		       (hratio << VI6_HGT_MODE_HRATIO_SHIFT) |
		       (vratio << VI6_HGT_MODE_VRATIO_SHIFT));
}