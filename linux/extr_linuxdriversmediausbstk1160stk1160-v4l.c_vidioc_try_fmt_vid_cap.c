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
struct v4l2_format {int dummy; } ;
struct stk1160 {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int stk1160_try_fmt (struct stk1160*,struct v4l2_format*,int /*<<< orphan*/ *) ; 
 struct stk1160* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct stk1160 *dev = video_drvdata(file);

	return stk1160_try_fmt(dev, f, NULL);
}