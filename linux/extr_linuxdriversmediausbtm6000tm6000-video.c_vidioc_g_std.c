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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {int /*<<< orphan*/  norm; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *norm)
{
	struct tm6000_fh *fh = priv;
	struct tm6000_core *dev = fh->dev;

	*norm = dev->norm;
	return 0;
}