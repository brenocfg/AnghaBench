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
struct TYPE_2__ {int verb; } ;
struct dpaa2_dq {TYPE_1__ dq; } ;

/* Variables and functions */
 int QBMAN_RESULT_BPSCN ; 
 int QBMAN_RESULT_MASK ; 

__attribute__((used)) static inline int qbman_result_is_BPSCN(const struct dpaa2_dq *dq)
{
	return ((dq->dq.verb & QBMAN_RESULT_MASK) == QBMAN_RESULT_BPSCN);
}