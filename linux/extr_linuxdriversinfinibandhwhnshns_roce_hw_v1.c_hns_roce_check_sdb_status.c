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
struct hns_roce_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ROCEE_CNT_CLR_CE_CNT_CLR_CE_S ; 
 int /*<<< orphan*/  ROCEE_SDB_RETRY_CNT_REG ; 
 int /*<<< orphan*/  ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_M ; 
 int /*<<< orphan*/  ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_S ; 
 int /*<<< orphan*/  ROCEE_SDB_SEND_PTR_REG ; 
 int /*<<< orphan*/  ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M ; 
 int /*<<< orphan*/  ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S ; 
 scalar_t__ SDB_ST_CMP_VAL ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  roce_get_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hns_roce_check_sdb_status(struct hns_roce_dev *hr_dev,
				      u32 *old_send, u32 *old_retry,
				      u32 *tsp_st, u32 *success_flags)
{
	__le32 *old_send_tmp, *old_retry_tmp;
	u32 sdb_retry_cnt;
	u32 sdb_send_ptr;
	u32 cur_cnt, old_cnt;
	__le32 tmp, tmp1;
	u32 send_ptr;

	sdb_send_ptr = roce_read(hr_dev, ROCEE_SDB_SEND_PTR_REG);
	sdb_retry_cnt =	roce_read(hr_dev, ROCEE_SDB_RETRY_CNT_REG);
	tmp = cpu_to_le32(sdb_send_ptr);
	tmp1 = cpu_to_le32(sdb_retry_cnt);
	cur_cnt = roce_get_field(tmp, ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M,
				 ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S) +
		  roce_get_field(tmp1, ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_M,
				 ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_S);

	old_send_tmp = (__le32 *)old_send;
	old_retry_tmp = (__le32 *)old_retry;
	if (!roce_get_bit(*tsp_st, ROCEE_CNT_CLR_CE_CNT_CLR_CE_S)) {
		old_cnt = roce_get_field(*old_send_tmp,
					 ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M,
					 ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S) +
			  roce_get_field(*old_retry_tmp,
					 ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_M,
					 ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_S);
		if (cur_cnt - old_cnt > SDB_ST_CMP_VAL)
			*success_flags = 1;
	} else {
		old_cnt = roce_get_field(*old_send_tmp,
					 ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M,
					 ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S);
		if (cur_cnt - old_cnt > SDB_ST_CMP_VAL) {
			*success_flags = 1;
		} else {
			send_ptr = roce_get_field(*old_send_tmp,
					    ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M,
					    ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S) +
				   roce_get_field(tmp1,
					    ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_M,
					    ROCEE_SDB_RETRY_CNT_SDB_RETRY_CT_S);
			roce_set_field(*old_send_tmp,
				       ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_M,
				       ROCEE_SDB_SEND_PTR_SDB_SEND_PTR_S,
				       send_ptr);
		}
	}
}