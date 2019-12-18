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
struct via_camera {int /*<<< orphan*/  sensor; } ;
struct v4l2_streamparm {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int v4l2_s_parm_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct via_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int viacam_s_parm(struct file *filp, void *priv,
		struct v4l2_streamparm *parm)
{
	struct via_camera *cam = video_drvdata(filp);

	return v4l2_s_parm_cap(video_devdata(filp), cam->sensor, parm);
}