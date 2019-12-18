#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  readbuffers; } ;
struct TYPE_4__ {TYPE_1__ capture; } ;
struct v4l2_streamparm {TYPE_2__ parm; } ;
struct mcam_camera {int /*<<< orphan*/  sensor; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  n_dma_bufs ; 
 int v4l2_g_parm_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct mcam_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int mcam_vidioc_g_parm(struct file *filp, void *priv,
		struct v4l2_streamparm *a)
{
	struct mcam_camera *cam = video_drvdata(filp);
	int ret;

	ret = v4l2_g_parm_cap(video_devdata(filp), cam->sensor, a);
	a->parm.capture.readbuffers = n_dma_bufs;
	return ret;
}