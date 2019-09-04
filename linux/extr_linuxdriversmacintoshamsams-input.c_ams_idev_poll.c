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
struct input_polled_dev {struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ zcalib; scalar_t__ ycalib; scalar_t__ xcalib; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 TYPE_1__ ams_info ; 
 int /*<<< orphan*/  ams_sensors (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ invert ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ams_idev_poll(struct input_polled_dev *dev)
{
	struct input_dev *idev = dev->input;
	s8 x, y, z;

	mutex_lock(&ams_info.lock);

	ams_sensors(&x, &y, &z);

	x -= ams_info.xcalib;
	y -= ams_info.ycalib;
	z -= ams_info.zcalib;

	input_report_abs(idev, ABS_X, invert ? -x : x);
	input_report_abs(idev, ABS_Y, invert ? -y : y);
	input_report_abs(idev, ABS_Z, z);

	input_sync(idev);

	mutex_unlock(&ams_info.lock);
}