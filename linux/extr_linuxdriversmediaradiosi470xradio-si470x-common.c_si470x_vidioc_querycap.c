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
struct v4l2_capability {int dummy; } ;
struct si470x_device {int (* vidioc_querycap ) (struct file*,void*,struct v4l2_capability*) ;} ;
struct file {int dummy; } ;

/* Variables and functions */
 int stub1 (struct file*,void*,struct v4l2_capability*) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_vidioc_querycap(struct file *file, void *priv,
		struct v4l2_capability *capability)
{
	struct si470x_device *radio = video_drvdata(file);

	return radio->vidioc_querycap(file, priv, capability);
}