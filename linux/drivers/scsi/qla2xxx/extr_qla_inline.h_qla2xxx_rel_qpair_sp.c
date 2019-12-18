#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qla_qpair {int /*<<< orphan*/  srb_mempool; } ;
struct TYPE_4__ {int /*<<< orphan*/ * qpair; } ;
typedef  TYPE_1__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_QPAIR_MARK_NOT_BUSY (struct qla_qpair*) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qla2xxx_rel_qpair_sp(struct qla_qpair *qpair, srb_t *sp)
{
	sp->qpair = NULL;
	mempool_free(sp, qpair->srb_mempool);
	QLA_QPAIR_MARK_NOT_BUSY(qpair);
}