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
struct TYPE_2__ {scalar_t__ rotate; } ;
struct vsp1_rwpf {unsigned int max_width; TYPE_1__ flip; } ;
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 struct vsp1_rwpf* to_rwpf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int wpf_max_width(struct vsp1_entity *entity,
				  struct vsp1_pipeline *pipe)
{
	struct vsp1_rwpf *wpf = to_rwpf(&entity->subdev);

	return wpf->flip.rotate ? 256 : wpf->max_width;
}