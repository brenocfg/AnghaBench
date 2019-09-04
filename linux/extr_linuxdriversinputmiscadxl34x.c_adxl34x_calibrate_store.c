#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {int x; int y; int z; } ;
struct TYPE_4__ {int x; int y; int z; } ;
struct adxl34x {int /*<<< orphan*/  mutex; TYPE_3__ hwcal; TYPE_2__ saved; TYPE_1__ swcal; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  AC_WRITE (struct adxl34x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFSX ; 
 int /*<<< orphan*/  OFSY ; 
 int /*<<< orphan*/  OFSZ ; 
 struct adxl34x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t adxl34x_calibrate_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	struct adxl34x *ac = dev_get_drvdata(dev);

	/*
	 * Hardware offset calibration has a resolution of 15.6 mg/LSB.
	 * We use HW calibration and handle the remaining bits in SW. (4mg/LSB)
	 */

	mutex_lock(&ac->mutex);
	ac->hwcal.x -= (ac->saved.x / 4);
	ac->swcal.x = ac->saved.x % 4;

	ac->hwcal.y -= (ac->saved.y / 4);
	ac->swcal.y = ac->saved.y % 4;

	ac->hwcal.z -= (ac->saved.z / 4);
	ac->swcal.z = ac->saved.z % 4;

	AC_WRITE(ac, OFSX, (s8) ac->hwcal.x);
	AC_WRITE(ac, OFSY, (s8) ac->hwcal.y);
	AC_WRITE(ac, OFSZ, (s8) ac->hwcal.z);
	mutex_unlock(&ac->mutex);

	return count;
}