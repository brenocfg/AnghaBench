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
struct file {int dummy; } ;
struct cx88_core {int /*<<< orphan*/  tvnorm; } ;
struct cx8800_dev {struct cx88_core* core; } ;

/* Variables and functions */
 struct cx8800_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *tvnorm)
{
	struct cx8800_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;

	*tvnorm = core->tvnorm;
	return 0;
}