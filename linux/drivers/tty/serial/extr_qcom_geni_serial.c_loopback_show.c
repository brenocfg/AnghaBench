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
struct qcom_geni_serial_port {int loopback; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct qcom_geni_serial_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static ssize_t loopback_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct qcom_geni_serial_port *port = dev_get_drvdata(dev);

	return snprintf(buf, sizeof(u32), "%d\n", port->loopback);
}