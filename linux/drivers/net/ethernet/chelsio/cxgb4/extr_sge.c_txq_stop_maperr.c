#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cntxt_id; int /*<<< orphan*/  stops; } ;
struct sge_uld_txq {TYPE_3__* adap; TYPE_1__ q; int /*<<< orphan*/  mapping_err; } ;
struct TYPE_5__ {int /*<<< orphan*/  txq_maperr; scalar_t__ egr_start; } ;
struct TYPE_6__ {TYPE_2__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void txq_stop_maperr(struct sge_uld_txq *q)
{
	q->mapping_err++;
	q->q.stops++;
	set_bit(q->q.cntxt_id - q->adap->sge.egr_start,
		q->adap->sge.txq_maperr);
}