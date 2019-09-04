#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; } ;
struct rxe_qp {TYPE_2__ attr; TYPE_1__ comp; } ;

/* Variables and functions */

__attribute__((used)) static inline void reset_retry_counters(struct rxe_qp *qp)
{
	qp->comp.retry_cnt = qp->attr.retry_cnt;
	qp->comp.rnr_retry = qp->attr.rnr_retry;
}