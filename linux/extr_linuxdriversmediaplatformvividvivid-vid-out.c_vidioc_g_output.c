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
struct vivid_dev {unsigned int output; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct vivid_dev* video_drvdata (struct file*) ; 

int vidioc_g_output(struct file *file, void *priv, unsigned *o)
{
	struct vivid_dev *dev = video_drvdata(file);

	*o = dev->output;
	return 0;
}