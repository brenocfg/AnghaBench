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
typedef  int /*<<< orphan*/  u16 ;
struct rvu {TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcifunc; } ;
struct npc_mcam_ena_dis_entry_req {int /*<<< orphan*/  entry; TYPE_2__ hdr; } ;
struct npc_mcam {int /*<<< orphan*/  lock; } ;
struct msg_rsp {int dummy; } ;
struct TYPE_3__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int NPC_MCAM_INVALID_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npc_enable_mcam_entry (struct rvu*,struct npc_mcam*,int,int /*<<< orphan*/ ,int) ; 
 int npc_mcam_verify_entry (struct npc_mcam*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rvu_mbox_handler_npc_mcam_ena_entry(struct rvu *rvu,
					struct npc_mcam_ena_dis_entry_req *req,
					struct msg_rsp *rsp)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcifunc = req->hdr.pcifunc;
	int blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	rc = npc_mcam_verify_entry(mcam, pcifunc, req->entry);
	mutex_unlock(&mcam->lock);
	if (rc)
		return rc;

	npc_enable_mcam_entry(rvu, mcam, blkaddr, req->entry, true);

	return 0;
}