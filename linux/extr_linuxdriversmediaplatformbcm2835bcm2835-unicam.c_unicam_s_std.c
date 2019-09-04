#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ v4l2_std_id ;
struct TYPE_4__ {scalar_t__ bytesperline; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct unicam_device {TYPE_3__ v_fmt; int /*<<< orphan*/  sensor; int /*<<< orphan*/  buffer_queue; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  g_std ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  unicam_reset_format (struct unicam_device*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_s_std(struct file *file, void *priv, v4l2_std_id std)
{
	struct unicam_device *dev = video_drvdata(file);
	int ret;
	v4l2_std_id current_std;

	ret = v4l2_subdev_call(dev->sensor, video, g_std, &current_std);
	if (ret)
		return ret;

	if (std == current_std)
		return 0;

	if (vb2_is_busy(&dev->buffer_queue))
		return -EBUSY;

	ret = v4l2_subdev_call(dev->sensor, video, s_std, std);

	/* Force recomputation of bytesperline */
	dev->v_fmt.fmt.pix.bytesperline = 0;

	unicam_reset_format(dev);

	return ret;
}