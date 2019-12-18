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
struct rvu {TYPE_1__* hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  bmap; } ;
struct npc_pkind {TYPE_2__ rsrc; } ;
struct TYPE_6__ {int /*<<< orphan*/  bmap; } ;
struct npc_mcam {int /*<<< orphan*/  lock; TYPE_3__ counters; } ;
struct TYPE_4__ {struct npc_mcam mcam; struct npc_pkind pkind; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void rvu_npc_freemem(struct rvu *rvu)
{
	struct npc_pkind *pkind = &rvu->hw->pkind;
	struct npc_mcam *mcam = &rvu->hw->mcam;

	kfree(pkind->rsrc.bmap);
	kfree(mcam->counters.bmap);
	mutex_destroy(&mcam->lock);
}