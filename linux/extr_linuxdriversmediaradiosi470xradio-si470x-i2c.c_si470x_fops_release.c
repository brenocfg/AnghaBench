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
struct si470x_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  si470x_stop (struct si470x_device*) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_release (struct file*) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_fops_release(struct file *file)
{
	struct si470x_device *radio = video_drvdata(file);

	if (v4l2_fh_is_singular_file(file))
		/* stop radio */
		si470x_stop(radio);

	return v4l2_fh_release(file);
}