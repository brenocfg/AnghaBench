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
struct TYPE_2__ {int /*<<< orphan*/  hr_buf; } ;
struct hns_roce_cq {TYPE_1__ hr_buf; } ;

/* Variables and functions */
 int HNS_ROCE_V1_CQE_ENTRY_SIZE ; 
 void* hns_roce_buf_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *get_cqe(struct hns_roce_cq *hr_cq, int n)
{
	return hns_roce_buf_offset(&hr_cq->hr_buf.hr_buf,
				   n * HNS_ROCE_V1_CQE_ENTRY_SIZE);
}