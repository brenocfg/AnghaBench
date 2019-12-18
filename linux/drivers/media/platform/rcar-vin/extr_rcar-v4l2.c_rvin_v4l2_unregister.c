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
struct rvin_dev {int /*<<< orphan*/  vdev; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

void rvin_v4l2_unregister(struct rvin_dev *vin)
{
	if (!video_is_registered(&vin->vdev))
		return;

	v4l2_info(&vin->v4l2_dev, "Removing %s\n",
		  video_device_node_name(&vin->vdev));

	/* Checks internally if vdev have been init or not */
	video_unregister_device(&vin->vdev);
}