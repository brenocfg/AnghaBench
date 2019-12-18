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
struct hns_roce_mbox_status {int /*<<< orphan*/  mb_status_hw_run; } ;
struct hns_roce_dev {int dummy; } ;
struct hns_roce_cmq_desc {scalar_t__ data; } ;
typedef  enum hns_roce_cmd_return_status { ____Placeholder_hns_roce_cmd_return_status } hns_roce_cmd_return_status ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_OPC_QUERY_MB_ST ; 
 int hns_roce_cmq_send (struct hns_roce_dev*,struct hns_roce_cmq_desc*,int) ; 
 int /*<<< orphan*/  hns_roce_cmq_setup_basic_desc (struct hns_roce_cmq_desc*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_query_mbox_status(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_cmq_desc desc;
	struct hns_roce_mbox_status *mb_st =
				       (struct hns_roce_mbox_status *)desc.data;
	enum hns_roce_cmd_return_status status;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_QUERY_MB_ST, true);

	status = hns_roce_cmq_send(hr_dev, &desc, 1);
	if (status)
		return status;

	return le32_to_cpu(mb_st->mb_status_hw_run);
}