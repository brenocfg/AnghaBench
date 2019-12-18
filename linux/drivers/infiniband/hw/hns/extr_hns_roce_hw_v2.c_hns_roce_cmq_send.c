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
struct hns_roce_dev {int dummy; } ;
struct hns_roce_cmq_desc {int dummy; } ;

/* Variables and functions */
 int CMD_RST_PRC_EBUSY ; 
 int CMD_RST_PRC_SUCCESS ; 
 int EBUSY ; 
 int __hns_roce_cmq_send (struct hns_roce_dev*,struct hns_roce_cmq_desc*,int) ; 
 int hns_roce_v2_rst_process_cmd (struct hns_roce_dev*) ; 

__attribute__((used)) static int hns_roce_cmq_send(struct hns_roce_dev *hr_dev,
			     struct hns_roce_cmq_desc *desc, int num)
{
	int retval;
	int ret;

	ret = hns_roce_v2_rst_process_cmd(hr_dev);
	if (ret == CMD_RST_PRC_SUCCESS)
		return 0;
	if (ret == CMD_RST_PRC_EBUSY)
		return -EBUSY;

	ret = __hns_roce_cmq_send(hr_dev, desc, num);
	if (ret) {
		retval = hns_roce_v2_rst_process_cmd(hr_dev);
		if (retval == CMD_RST_PRC_SUCCESS)
			return 0;
		else if (retval == CMD_RST_PRC_EBUSY)
			return -EBUSY;
	}

	return ret;
}