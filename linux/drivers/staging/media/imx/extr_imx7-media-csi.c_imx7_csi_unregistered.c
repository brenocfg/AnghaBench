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
struct v4l2_subdev {int dummy; } ;
struct imx7_csi {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_media_capture_device_unregister (int /*<<< orphan*/ ) ; 
 struct imx7_csi* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void imx7_csi_unregistered(struct v4l2_subdev *sd)
{
	struct imx7_csi *csi = v4l2_get_subdevdata(sd);

	imx_media_capture_device_unregister(csi->vdev);
}