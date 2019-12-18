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
struct srpt_rdma_ch {int /*<<< orphan*/  cq; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_free_cq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srpt_destroy_ch_ib(struct srpt_rdma_ch *ch)
{
	ib_destroy_qp(ch->qp);
	ib_free_cq(ch->cq);
}