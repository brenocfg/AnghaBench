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
struct tm6000_fh {int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct tm6000_core* dev; } ;
struct tm6000_core {int /*<<< orphan*/  norm; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_std ; 
 int tm6000_init_analog_mode (struct tm6000_core*) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id norm)
{
	int rc = 0;
	struct tm6000_fh *fh = priv;
	struct tm6000_core *dev = fh->dev;

	dev->norm = norm;
	rc = tm6000_init_analog_mode(dev);

	fh->width  = dev->width;
	fh->height = dev->height;

	if (rc < 0)
		return rc;

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std, dev->norm);

	return 0;
}