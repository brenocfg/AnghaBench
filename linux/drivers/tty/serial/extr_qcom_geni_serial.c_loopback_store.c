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
typedef  scalar_t__ u32 ;
struct qcom_geni_serial_port {scalar_t__ loopback; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ MAX_LOOPBACK_CFG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct qcom_geni_serial_port* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static ssize_t loopback_store(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t size)
{
	struct qcom_geni_serial_port *port = dev_get_drvdata(dev);
	u32 loopback;

	if (kstrtoint(buf, 0, &loopback) || loopback > MAX_LOOPBACK_CFG) {
		dev_err(dev, "Invalid input\n");
		return -EINVAL;
	}
	port->loopback = loopback;
	return size;
}