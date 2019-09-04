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
typedef  scalar_t__ u8 ;
struct nicvf {int sqs_id; scalar_t__ sqs_mode; } ;

/* Variables and functions */
 int MAX_CMP_QUEUES_PER_QS ; 

__attribute__((used)) static inline u8 nicvf_netdev_qidx(struct nicvf *nic, u8 qidx)
{
	if (nic->sqs_mode)
		return qidx + ((nic->sqs_id + 1) * MAX_CMP_QUEUES_PER_QS);
	else
		return qidx;
}