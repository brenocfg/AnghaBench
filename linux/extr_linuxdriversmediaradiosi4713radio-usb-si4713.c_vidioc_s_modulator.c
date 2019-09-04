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
struct v4l2_modulator {int dummy; } ;
struct si4713_usb_device {int /*<<< orphan*/  v4l2_subdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_modulator ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_modulator const*) ; 
 struct si4713_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_modulator(struct file *file, void *priv,
				const struct v4l2_modulator *vm)
{
	struct si4713_usb_device *radio = video_drvdata(file);

	return v4l2_subdev_call(radio->v4l2_subdev, tuner, s_modulator, vm);
}