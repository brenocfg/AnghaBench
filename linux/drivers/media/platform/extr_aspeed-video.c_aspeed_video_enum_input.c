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
struct v4l2_input {int /*<<< orphan*/  status; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  type; int /*<<< orphan*/  name; scalar_t__ index; } ;
struct file {int dummy; } ;
struct aspeed_video {int /*<<< orphan*/  v4l2_input_status; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_IN_CAP_DV_TIMINGS ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct aspeed_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int aspeed_video_enum_input(struct file *file, void *fh,
				   struct v4l2_input *inp)
{
	struct aspeed_video *video = video_drvdata(file);

	if (inp->index)
		return -EINVAL;

	strscpy(inp->name, "Host VGA capture", sizeof(inp->name));
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;
	inp->status = video->v4l2_input_status;

	return 0;
}