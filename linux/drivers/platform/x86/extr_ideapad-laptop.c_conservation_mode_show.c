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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CONSERVATION_BIT ; 
 struct ideapad_private* dev_get_drvdata (struct device*) ; 
 scalar_t__ method_gbmd (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t conservation_mode_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct ideapad_private *priv = dev_get_drvdata(dev);
	unsigned long result;

	if (method_gbmd(priv->adev->handle, &result))
		return sprintf(buf, "-1\n");
	return sprintf(buf, "%u\n", test_bit(BM_CONSERVATION_BIT, &result));
}