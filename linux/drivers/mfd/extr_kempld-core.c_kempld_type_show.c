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
struct kempld_device_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct kempld_device_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kempld_get_type_string (struct kempld_device_data*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t kempld_type_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct kempld_device_data *pld = dev_get_drvdata(dev);

	return scnprintf(buf, PAGE_SIZE, "%s\n", kempld_get_type_string(pld));
}