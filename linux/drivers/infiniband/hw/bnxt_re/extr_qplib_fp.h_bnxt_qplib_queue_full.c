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
struct TYPE_2__ {scalar_t__ cons; scalar_t__ prod; } ;
struct bnxt_qplib_q {TYPE_1__ hwq; scalar_t__ q_full_delta; } ;

/* Variables and functions */
 scalar_t__ HWQ_CMP (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static inline bool bnxt_qplib_queue_full(struct bnxt_qplib_q *qplib_q)
{
	return HWQ_CMP((qplib_q->hwq.prod + qplib_q->q_full_delta),
		       &qplib_q->hwq) == HWQ_CMP(qplib_q->hwq.cons,
						 &qplib_q->hwq);
}