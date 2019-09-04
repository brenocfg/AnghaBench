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

/* Variables and functions */
 int rmi_f54_set_input (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  video_drvdata (struct file*) ; 

__attribute__((used)) static int rmi_f54_vidioc_s_input(struct file *file, void *priv, unsigned int i)
{
	return rmi_f54_set_input(video_drvdata(file), i);
}