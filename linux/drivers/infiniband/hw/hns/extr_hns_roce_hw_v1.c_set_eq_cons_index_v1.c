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
struct hns_roce_eq {int cons_index; int log_entries; int /*<<< orphan*/  doorbell; } ;

/* Variables and functions */
 int HNS_ROCE_V1_CONS_IDX_M ; 
 int /*<<< orphan*/  roce_raw_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_eq_cons_index_v1(struct hns_roce_eq *eq, int req_not)
{
	roce_raw_write((eq->cons_index & HNS_ROCE_V1_CONS_IDX_M) |
		      (req_not << eq->log_entries), eq->doorbell);
}