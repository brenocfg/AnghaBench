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
struct vsp1_histogram {int /*<<< orphan*/  entity; } ;
struct v4l2_rect {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_subdev_selection {struct v4l2_rect r; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SEL_TGT_COMPOSE ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 void* clamp (int,int,int) ; 
 struct vsp1_histogram* subdev_to_histo (struct v4l2_subdev*) ; 
 struct v4l2_rect* vsp1_entity_get_pad_selection (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int histo_set_compose(struct v4l2_subdev *subdev,
			     struct v4l2_subdev_pad_config *config,
			     struct v4l2_subdev_selection *sel)
{
	struct vsp1_histogram *histo = subdev_to_histo(subdev);
	struct v4l2_rect *compose;
	struct v4l2_rect *crop;
	unsigned int ratio;

	/*
	 * The compose rectangle is used to configure downscaling, the top left
	 * corner is fixed to (0,0) and the size to 1/2 or 1/4 of the crop
	 * rectangle.
	 */
	sel->r.left = 0;
	sel->r.top = 0;

	crop = vsp1_entity_get_pad_selection(&histo->entity, config, sel->pad,
					     V4L2_SEL_TGT_CROP);

	/*
	 * Clamp the width and height to acceptable values first and then
	 * compute the closest rounded dividing ratio.
	 *
	 * Ratio	Rounded ratio
	 * --------------------------
	 * [1.0 1.5[	1
	 * [1.5 3.0[	2
	 * [3.0 4.0]	4
	 *
	 * The rounded ratio can be computed using
	 *
	 * 1 << (ceil(ratio * 2) / 3)
	 */
	sel->r.width = clamp(sel->r.width, crop->width / 4, crop->width);
	ratio = 1 << (crop->width * 2 / sel->r.width / 3);
	sel->r.width = crop->width / ratio;


	sel->r.height = clamp(sel->r.height, crop->height / 4, crop->height);
	ratio = 1 << (crop->height * 2 / sel->r.height / 3);
	sel->r.height = crop->height / ratio;

	compose = vsp1_entity_get_pad_selection(&histo->entity, config,
						sel->pad,
						V4L2_SEL_TGT_COMPOSE);
	*compose = sel->r;

	return 0;
}