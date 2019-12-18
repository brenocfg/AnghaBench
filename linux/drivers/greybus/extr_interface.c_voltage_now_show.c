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
typedef  int u32 ;
struct gb_interface {int /*<<< orphan*/  dev; int /*<<< orphan*/  interface_id; TYPE_1__* hd; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_PWRMON_TYPE_VOL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_svc_pwrmon_intf_sample_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 
 struct gb_interface* to_gb_interface (struct device*) ; 

__attribute__((used)) static ssize_t voltage_now_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct gb_interface *intf = to_gb_interface(dev);
	int ret;
	u32 measurement;

	ret = gb_svc_pwrmon_intf_sample_get(intf->hd->svc, intf->interface_id,
					    GB_SVC_PWRMON_TYPE_VOL,
					    &measurement);
	if (ret) {
		dev_err(&intf->dev, "failed to get voltage sample (%d)\n", ret);
		return ret;
	}

	return sprintf(buf, "%u\n", measurement);
}