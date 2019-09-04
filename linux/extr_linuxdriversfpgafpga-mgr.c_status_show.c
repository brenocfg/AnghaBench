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
typedef  int u64 ;
struct fpga_manager {TYPE_1__* mops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* status ) (struct fpga_manager*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int FPGA_MGR_STATUS_CRC_ERR ; 
 int FPGA_MGR_STATUS_FIFO_OVERFLOW_ERR ; 
 int FPGA_MGR_STATUS_INCOMPATIBLE_IMAGE_ERR ; 
 int FPGA_MGR_STATUS_IP_PROTOCOL_ERR ; 
 int FPGA_MGR_STATUS_OPERATION_ERR ; 
 scalar_t__ sprintf (char*,char*) ; 
 int stub1 (struct fpga_manager*) ; 
 struct fpga_manager* to_fpga_manager (struct device*) ; 

__attribute__((used)) static ssize_t status_show(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct fpga_manager *mgr = to_fpga_manager(dev);
	u64 status;
	int len = 0;

	if (!mgr->mops->status)
		return -ENOENT;

	status = mgr->mops->status(mgr);

	if (status & FPGA_MGR_STATUS_OPERATION_ERR)
		len += sprintf(buf + len, "reconfig operation error\n");
	if (status & FPGA_MGR_STATUS_CRC_ERR)
		len += sprintf(buf + len, "reconfig CRC error\n");
	if (status & FPGA_MGR_STATUS_INCOMPATIBLE_IMAGE_ERR)
		len += sprintf(buf + len, "reconfig incompatible image\n");
	if (status & FPGA_MGR_STATUS_IP_PROTOCOL_ERR)
		len += sprintf(buf + len, "reconfig IP protocol error\n");
	if (status & FPGA_MGR_STATUS_FIFO_OVERFLOW_ERR)
		len += sprintf(buf + len, "reconfig fifo overflow error\n");

	return len;
}