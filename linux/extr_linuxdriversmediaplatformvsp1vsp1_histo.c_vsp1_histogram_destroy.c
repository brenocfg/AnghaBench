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
struct vsp1_histogram {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 struct vsp1_histogram* subdev_to_histo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_histogram_cleanup (struct vsp1_histogram*) ; 

void vsp1_histogram_destroy(struct vsp1_entity *entity)
{
	struct vsp1_histogram *histo = subdev_to_histo(&entity->subdev);

	vsp1_histogram_cleanup(histo);
}