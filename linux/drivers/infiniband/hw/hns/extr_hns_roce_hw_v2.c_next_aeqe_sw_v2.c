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
struct hns_roce_eq {int cons_index; int entries; int /*<<< orphan*/  hop_num; } ;
struct hns_roce_aeqe {int /*<<< orphan*/  asyn; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_V2_AEQ_AEQE_OWNER_S ; 
 struct hns_roce_aeqe* get_aeqe_v2 (struct hns_roce_eq*,int) ; 
 struct hns_roce_aeqe* mhop_get_aeqe (struct hns_roce_eq*,int) ; 
 int roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hns_roce_aeqe *next_aeqe_sw_v2(struct hns_roce_eq *eq)
{
	struct hns_roce_aeqe *aeqe;

	if (!eq->hop_num)
		aeqe = get_aeqe_v2(eq, eq->cons_index);
	else
		aeqe = mhop_get_aeqe(eq, eq->cons_index);

	return (roce_get_bit(aeqe->asyn, HNS_ROCE_V2_AEQ_AEQE_OWNER_S) ^
		!!(eq->cons_index & eq->entries)) ? aeqe : NULL;
}