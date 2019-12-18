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
struct ideapad_private {TYPE_1__* adev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HACMD_FNLOCK_OFF ; 
 int /*<<< orphan*/  HACMD_FNLOCK_ON ; 
 struct ideapad_private* dev_get_drvdata (struct device*) ; 
 int kstrtobool (char const*,int*) ; 
 int method_int1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fn_lock_store(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct ideapad_private *priv = dev_get_drvdata(dev);
	bool state;
	int ret;

	ret = kstrtobool(buf, &state);
	if (ret)
		return ret;

	ret = method_int1(priv->adev->handle, "SALS", state ?
			  HACMD_FNLOCK_ON :
			  HACMD_FNLOCK_OFF);
	if (ret < 0)
		return -EIO;
	return count;
}