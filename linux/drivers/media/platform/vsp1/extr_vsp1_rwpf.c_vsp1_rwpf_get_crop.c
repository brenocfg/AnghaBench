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
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;
struct vsp1_rwpf {TYPE_1__ entity; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_rect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RWPF_PAD_SINK ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

struct v4l2_rect *vsp1_rwpf_get_crop(struct vsp1_rwpf *rwpf,
				     struct v4l2_subdev_pad_config *config)
{
	return v4l2_subdev_get_try_crop(&rwpf->entity.subdev, config,
					RWPF_PAD_SINK);
}