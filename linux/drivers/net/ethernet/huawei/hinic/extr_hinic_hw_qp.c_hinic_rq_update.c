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
typedef  scalar_t__ u16 ;
struct hinic_rq {int /*<<< orphan*/ * pi_virt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_MASKED_IDX (struct hinic_rq*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

void hinic_rq_update(struct hinic_rq *rq, u16 prod_idx)
{
	*rq->pi_virt_addr = cpu_to_be16(RQ_MASKED_IDX(rq, prod_idx + 1));
}