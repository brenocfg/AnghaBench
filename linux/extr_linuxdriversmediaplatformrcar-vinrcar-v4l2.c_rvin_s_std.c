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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct rvin_dev {int /*<<< orphan*/  std; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int rvin_reset_format (struct rvin_dev*) ; 
 int /*<<< orphan*/  s_std ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 struct rvin_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vin_to_source (struct rvin_dev*) ; 

__attribute__((used)) static int rvin_s_std(struct file *file, void *priv, v4l2_std_id a)
{
	struct rvin_dev *vin = video_drvdata(file);
	int ret;

	ret = v4l2_subdev_call(vin_to_source(vin), video, s_std, a);
	if (ret < 0)
		return ret;

	vin->std = a;

	/* Changing the standard will change the width/height */
	return rvin_reset_format(vin);
}