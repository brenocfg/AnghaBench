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
struct soc_camera_subdev_desc {int /*<<< orphan*/  (* free_bus ) (struct soc_camera_subdev_desc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct soc_camera_subdev_desc*) ; 

__attribute__((used)) static void mt9m001_video_remove(struct soc_camera_subdev_desc *ssdd)
{
	if (ssdd->free_bus)
		ssdd->free_bus(ssdd);
}