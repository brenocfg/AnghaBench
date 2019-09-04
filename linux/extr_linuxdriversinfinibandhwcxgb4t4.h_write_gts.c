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
typedef  int u32 ;
struct t4_cq {scalar_t__ gts; int /*<<< orphan*/  cqid; scalar_t__ bar2_va; int /*<<< orphan*/  bar2_qid; } ;

/* Variables and functions */
 int INGRESSQID_V (int /*<<< orphan*/ ) ; 
 scalar_t__ SGE_UDB_GTS ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void write_gts(struct t4_cq *cq, u32 val)
{
	if (cq->bar2_va)
		writel(val | INGRESSQID_V(cq->bar2_qid),
		       cq->bar2_va + SGE_UDB_GTS);
	else
		writel(val | INGRESSQID_V(cq->cqid), cq->gts);
}