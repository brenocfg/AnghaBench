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
struct f54_data {unsigned int input; } ;

/* Variables and functions */
 struct f54_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int rmi_f54_vidioc_g_input(struct file *file, void *priv,
				  unsigned int *i)
{
	struct f54_data *f54 = video_drvdata(file);

	*i = f54->input;

	return 0;
}