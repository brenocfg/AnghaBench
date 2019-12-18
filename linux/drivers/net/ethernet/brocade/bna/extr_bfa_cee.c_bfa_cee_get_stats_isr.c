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
struct bfa_cee_stats {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_stats_cbarg; int /*<<< orphan*/  (* get_stats_cbfn ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  kva; } ;
struct bfa_cee {int get_stats_status; int get_stats_pending; TYPE_2__ cbfn; int /*<<< orphan*/  stats; TYPE_1__ stats_dma; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_cee_stats_swap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_cee_get_stats_isr(struct bfa_cee *cee, enum bfa_status status)
{
	cee->get_stats_status = status;
	if (status == BFA_STATUS_OK) {
		memcpy(cee->stats, cee->stats_dma.kva,
			sizeof(struct bfa_cee_stats));
		bfa_cee_stats_swap(cee->stats);
	}
	cee->get_stats_pending = false;
	if (cee->cbfn.get_stats_cbfn)
		cee->cbfn.get_stats_cbfn(cee->cbfn.get_stats_cbarg, status);
}