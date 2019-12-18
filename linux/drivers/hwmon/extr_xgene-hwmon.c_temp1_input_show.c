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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_hwmon_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int CELSIUS_TO_mCELSIUS (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TEMP_NEGATIVE_BIT ; 
 struct xgene_hwmon_dev* dev_get_drvdata (struct device*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int xgene_hwmon_get_temp (struct xgene_hwmon_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t temp1_input_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct xgene_hwmon_dev *ctx = dev_get_drvdata(dev);
	int rc, temp;
	u32 val;

	rc = xgene_hwmon_get_temp(ctx, &val);
	if (rc < 0)
		return rc;

	temp = sign_extend32(val, TEMP_NEGATIVE_BIT);

	return snprintf(buf, PAGE_SIZE, "%d\n", CELSIUS_TO_mCELSIUS(temp));
}