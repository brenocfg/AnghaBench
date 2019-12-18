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
struct v4l2_tuner {scalar_t__ index; } ;
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {int /*<<< orphan*/  v4l2_dev; } ;
struct file {struct tm6000_fh* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  s_tuner ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner const*) ; 

__attribute__((used)) static int radio_s_tuner(struct file *file, void *priv,
					const struct v4l2_tuner *t)
{
	struct tm6000_fh *fh = file->private_data;
	struct tm6000_core *dev = fh->dev;

	if (0 != t->index)
		return -EINVAL;
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_tuner, t);
	return 0;
}