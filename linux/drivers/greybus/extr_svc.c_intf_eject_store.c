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
struct gb_svc {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned short) ; 
 int gb_svc_intf_eject (struct gb_svc*,unsigned short) ; 
 int kstrtou16 (char const*,int,unsigned short*) ; 
 struct gb_svc* to_gb_svc (struct device*) ; 

__attribute__((used)) static ssize_t intf_eject_store(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t len)
{
	struct gb_svc *svc = to_gb_svc(dev);
	unsigned short intf_id;
	int ret;

	ret = kstrtou16(buf, 10, &intf_id);
	if (ret < 0)
		return ret;

	dev_warn(dev, "Forcibly trying to eject interface %d\n", intf_id);

	ret = gb_svc_intf_eject(svc, intf_id);
	if (ret < 0)
		return ret;

	return len;
}