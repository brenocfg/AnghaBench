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
struct qed_hwfn {TYPE_1__* p_consq; } ;
struct TYPE_2__ {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  qed_chain_reset (int /*<<< orphan*/ *) ; 

void qed_consq_setup(struct qed_hwfn *p_hwfn)
{
	qed_chain_reset(&p_hwfn->p_consq->chain);
}