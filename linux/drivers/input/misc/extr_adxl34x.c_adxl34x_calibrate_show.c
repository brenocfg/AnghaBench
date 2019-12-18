#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int x; int y; int z; } ;
struct TYPE_3__ {int x; int y; int z; } ;
struct adxl34x {int /*<<< orphan*/  mutex; TYPE_2__ swcal; TYPE_1__ hwcal; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct adxl34x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static ssize_t adxl34x_calibrate_show(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct adxl34x *ac = dev_get_drvdata(dev);
	ssize_t count;

	mutex_lock(&ac->mutex);
	count = sprintf(buf, "%d,%d,%d\n",
			ac->hwcal.x * 4 + ac->swcal.x,
			ac->hwcal.y * 4 + ac->swcal.y,
			ac->hwcal.z * 4 + ac->swcal.z);
	mutex_unlock(&ac->mutex);

	return count;
}