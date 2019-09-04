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
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {unsigned int video_input; } ;

/* Variables and functions */

int cx231xx_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;

	*i = dev->video_input;

	return 0;
}