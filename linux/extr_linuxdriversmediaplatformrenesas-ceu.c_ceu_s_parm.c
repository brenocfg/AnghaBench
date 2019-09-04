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
struct v4l2_streamparm {int dummy; } ;
struct file {int dummy; } ;
struct ceu_device {TYPE_1__* sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_sd; } ;

/* Variables and functions */
 int v4l2_s_parm_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct ceu_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int ceu_s_parm(struct file *file, void *fh, struct v4l2_streamparm *a)
{
	struct ceu_device *ceudev = video_drvdata(file);

	return v4l2_s_parm_cap(video_devdata(file), ceudev->sd->v4l2_sd, a);
}