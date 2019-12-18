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
struct stk1160 {unsigned int ctl_input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int STK1160_MAX_INPUT ; 
 int /*<<< orphan*/  stk1160_select_input (struct stk1160*) ; 
 struct stk1160* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int i)
{
	struct stk1160 *dev = video_drvdata(file);

	if (i > STK1160_MAX_INPUT)
		return -EINVAL;

	dev->ctl_input = i;

	stk1160_select_input(dev);

	return 0;
}