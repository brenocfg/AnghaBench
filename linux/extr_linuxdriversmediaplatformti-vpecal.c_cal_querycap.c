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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct TYPE_2__ {char* name; } ;
struct cal_ctx {TYPE_1__ v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_MODULE_NAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cal_ctx* video_drvdata (struct file*) ; 

__attribute__((used)) static int cal_querycap(struct file *file, void *priv,
			struct v4l2_capability *cap)
{
	struct cal_ctx *ctx = video_drvdata(file);

	strlcpy(cap->driver, CAL_MODULE_NAME, sizeof(cap->driver));
	strlcpy(cap->card, CAL_MODULE_NAME, sizeof(cap->card));

	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "platform:%s", ctx->v4l2_dev.name);
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
			    V4L2_CAP_READWRITE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}