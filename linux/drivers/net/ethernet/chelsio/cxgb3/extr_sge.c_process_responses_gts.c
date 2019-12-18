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
struct sge_rspq {int /*<<< orphan*/  cidx; int /*<<< orphan*/  next_holdoff; int /*<<< orphan*/  cntxt_id; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_GTS ; 
 int V_NEWINDEX (int /*<<< orphan*/ ) ; 
 int V_NEWTIMER (int /*<<< orphan*/ ) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 int process_responses (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rspq_to_qset (struct sge_rspq*) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int process_responses_gts(struct adapter *adap,
					struct sge_rspq *rq)
{
	int work;

	work = process_responses(adap, rspq_to_qset(rq), -1);
	t3_write_reg(adap, A_SG_GTS, V_RSPQ(rq->cntxt_id) |
		     V_NEWTIMER(rq->next_holdoff) | V_NEWINDEX(rq->cidx));
	return work;
}