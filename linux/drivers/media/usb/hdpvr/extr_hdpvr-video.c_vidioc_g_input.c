#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int video_input; } ;
struct hdpvr_device {TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_input(struct file *file, void *private_data,
			  unsigned int *index)
{
	struct hdpvr_device *dev = video_drvdata(file);

	*index = dev->options.video_input;
	return 0;
}