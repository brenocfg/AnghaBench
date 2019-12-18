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
typedef  int u32 ;
struct ib_cq {int dummy; } ;
struct hns_roce_cq {int cons_index; int cq_depth; int cqn; int /*<<< orphan*/  cq_db_l; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CQ_DB_REQ_NOT ; 
 int CQ_DB_REQ_NOT_SOL ; 
 int IB_CQ_SOLICITED ; 
 int IB_CQ_SOLICITED_MASK ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_M ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_M ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_S ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_S ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_HW_SYNS_S ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_M ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  hns_roce_write64_k (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hns_roce_cq* to_hr_cq (struct ib_cq*) ; 

__attribute__((used)) static int hns_roce_v1_req_notify_cq(struct ib_cq *ibcq,
				     enum ib_cq_notify_flags flags)
{
	struct hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	u32 notification_flag;
	__le32 doorbell[2] = {};

	notification_flag = (flags & IB_CQ_SOLICITED_MASK) ==
			    IB_CQ_SOLICITED ? CQ_DB_REQ_NOT : CQ_DB_REQ_NOT_SOL;
	/*
	 * flags = 0; Notification Flag = 1, next
	 * flags = 1; Notification Flag = 0, solocited
	 */
	doorbell[0] =
		cpu_to_le32(hr_cq->cons_index & ((hr_cq->cq_depth << 1) - 1));
	roce_set_bit(doorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_HW_SYNS_S, 1);
	roce_set_field(doorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_S, 3);
	roce_set_field(doorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_S, 1);
	roce_set_field(doorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_S,
		       hr_cq->cqn | notification_flag);

	hns_roce_write64_k(doorbell, hr_cq->cq_db_l);

	return 0;
}