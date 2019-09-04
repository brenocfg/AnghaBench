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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {scalar_t__ tuner_type; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  freq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency const*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				const struct v4l2_frequency *f)
{
	struct tm6000_fh   *fh  = priv;
	struct tm6000_core *dev = fh->dev;

	if (UNSET == dev->tuner_type)
		return -ENOTTY;
	if (f->tuner != 0)
		return -EINVAL;

	dev->freq = f->frequency;
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, f);

	return 0;
}