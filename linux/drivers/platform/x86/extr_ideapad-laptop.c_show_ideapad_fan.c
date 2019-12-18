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
 int /*<<< orphan*/  VPCCMD_R_FAN ; 
 struct ideapad_private* dev_get_drvdata (struct device*) ; 
 scalar_t__ read_ec_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t show_ideapad_fan(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	unsigned long result;
	struct ideapad_private *priv = dev_get_drvdata(dev);

	if (read_ec_data(priv->adev->handle, VPCCMD_R_FAN, &result))
		return sprintf(buf, "-1\n");
	return sprintf(buf, "%lu\n", result);
}