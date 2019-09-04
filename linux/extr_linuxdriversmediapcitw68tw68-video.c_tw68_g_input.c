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
struct tw68_dev {unsigned int input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct tw68_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw68_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct tw68_dev *dev = video_drvdata(file);

	*i = dev->input;
	return 0;
}