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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hns_roce_eq {int eqe_buf_pg_sz; int entries; scalar_t__ hop_num; scalar_t__* buf; scalar_t__ bt_l0; } ;
struct hns_roce_aeqe {int dummy; } ;

/* Variables and functions */
 int HNS_ROCE_AEQ_ENTRY_SIZE ; 
 scalar_t__ HNS_ROCE_HOP_NUM_0 ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static struct hns_roce_aeqe *mhop_get_aeqe(struct hns_roce_eq *eq, u32 entry)
{
	u32 buf_chk_sz;
	unsigned long off;

	buf_chk_sz = 1 << (eq->eqe_buf_pg_sz + PAGE_SHIFT);

	off = (entry & (eq->entries - 1)) * HNS_ROCE_AEQ_ENTRY_SIZE;

	if (eq->hop_num == HNS_ROCE_HOP_NUM_0)
		return (struct hns_roce_aeqe *)((u8 *)(eq->bt_l0) +
			off % buf_chk_sz);
	else
		return (struct hns_roce_aeqe *)((u8 *)
			(eq->buf[off / buf_chk_sz]) + off % buf_chk_sz);
}