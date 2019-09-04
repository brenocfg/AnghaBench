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
struct v4l2_frequency {int dummy; } ;
struct timbradio {int /*<<< orphan*/  sd_tuner; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 struct timbradio* video_drvdata (struct file*) ; 

__attribute__((used)) static int timbradio_vidioc_g_frequency(struct file *file, void *priv,
	struct v4l2_frequency *f)
{
	struct timbradio *tr = video_drvdata(file);
	return v4l2_subdev_call(tr->sd_tuner, tuner, g_frequency, f);
}