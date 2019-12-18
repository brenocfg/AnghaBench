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
typedef  int /*<<< orphan*/  u16 ;
struct rvu {TYPE_1__* hw; } ;
struct npc_mcam {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npc_mcam_free_all_counters (struct rvu*,struct npc_mcam*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npc_mcam_free_all_entries (struct rvu*,struct npc_mcam*,int,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_npc_disable_default_entries (struct rvu*,int /*<<< orphan*/ ,int) ; 

void rvu_npc_disable_mcam_entries(struct rvu *rvu, u16 pcifunc, int nixlf)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	int blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return;

	mutex_lock(&mcam->lock);

	/* Disable and free all MCAM entries mapped to this 'pcifunc' */
	npc_mcam_free_all_entries(rvu, mcam, blkaddr, pcifunc);

	/* Free all MCAM counters mapped to this 'pcifunc' */
	npc_mcam_free_all_counters(rvu, mcam, pcifunc);

	mutex_unlock(&mcam->lock);

	rvu_npc_disable_default_entries(rvu, pcifunc, nixlf);
}