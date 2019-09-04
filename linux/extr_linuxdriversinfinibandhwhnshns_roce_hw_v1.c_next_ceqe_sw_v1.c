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
struct hns_roce_eq {int cons_index; int entries; } ;
struct hns_roce_ceqe {int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_CEQE_CEQE_COMP_OWNER_S ; 
 struct hns_roce_ceqe* get_ceqe_v1 (struct hns_roce_eq*,int) ; 
 int /*<<< orphan*/  roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hns_roce_ceqe *next_ceqe_sw_v1(struct hns_roce_eq *eq)
{
	struct hns_roce_ceqe *ceqe = get_ceqe_v1(eq, eq->cons_index);

	return (!!(roce_get_bit(ceqe->comp,
		HNS_ROCE_CEQE_CEQE_COMP_OWNER_S))) ^
		(!!(eq->cons_index & eq->entries)) ? ceqe : NULL;
}