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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dcon_set_mono_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t dcon_mono_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	unsigned long enable_mono;
	int rc;

	rc = kstrtoul(buf, 10, &enable_mono);
	if (rc)
		return rc;

	dcon_set_mono_mode(dev_get_drvdata(dev), enable_mono ? true : false);

	return count;
}