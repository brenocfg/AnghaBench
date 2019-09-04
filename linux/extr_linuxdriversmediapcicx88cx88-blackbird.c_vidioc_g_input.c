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
struct file {int dummy; } ;
struct cx88_core {unsigned int input; } ;
struct cx8802_dev {struct cx88_core* core; } ;

/* Variables and functions */
 struct cx8802_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct cx8802_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;

	*i = core->input;
	return 0;
}