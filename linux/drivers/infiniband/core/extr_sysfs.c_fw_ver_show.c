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
struct ib_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_FW_VERSION_NAME_MAX ; 
 int /*<<< orphan*/  ib_get_device_fw_str (struct ib_device*,char*) ; 
 struct ib_device* rdma_device_to_ibdev (struct device*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t fw_ver_show(struct device *device, struct device_attribute *attr,
			   char *buf)
{
	struct ib_device *dev = rdma_device_to_ibdev(device);

	ib_get_device_fw_str(dev, buf);
	strlcat(buf, "\n", IB_FW_VERSION_NAME_MAX);
	return strlen(buf);
}