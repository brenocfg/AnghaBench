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
struct TYPE_2__ {int first; } ;
union sub_crq {TYPE_1__ generic; } ;
struct ibmvnic_sub_crq_queue {size_t cur; union sub_crq* msgs; } ;
struct ibmvnic_adapter {int dummy; } ;

/* Variables and functions */
 int IBMVNIC_CRQ_CMD_RSP ; 

__attribute__((used)) static int pending_scrq(struct ibmvnic_adapter *adapter,
			struct ibmvnic_sub_crq_queue *scrq)
{
	union sub_crq *entry = &scrq->msgs[scrq->cur];

	if (entry->generic.first & IBMVNIC_CRQ_CMD_RSP)
		return 1;
	else
		return 0;
}