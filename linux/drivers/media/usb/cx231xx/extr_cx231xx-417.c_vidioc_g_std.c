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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct file {struct cx231xx_fh* private_data; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct cx231xx {TYPE_1__ encodernorm; } ;

/* Variables and functions */

__attribute__((used)) static int vidioc_g_std(struct file *file, void *fh0, v4l2_std_id *norm)
{
	struct cx231xx_fh  *fh  = file->private_data;
	struct cx231xx *dev = fh->dev;

	*norm = dev->encodernorm.id;
	return 0;
}