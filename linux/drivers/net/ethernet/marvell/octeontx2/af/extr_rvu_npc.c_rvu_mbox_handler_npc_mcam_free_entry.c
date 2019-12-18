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
typedef  scalar_t__ u16 ;
struct rvu {TYPE_1__* hw; } ;
struct TYPE_4__ {scalar_t__ pcifunc; } ;
struct npc_mcam_free_entry_req {size_t entry; scalar_t__ all; TYPE_2__ hdr; } ;
struct npc_mcam {scalar_t__* entry2cntr_map; int /*<<< orphan*/  lock; scalar_t__* entry2pfvf_map; } ;
struct msg_rsp {int dummy; } ;
struct TYPE_3__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 scalar_t__ NPC_MCAM_INVALID_MAP ; 
 int NPC_MCAM_INVALID_REQ ; 
 int /*<<< orphan*/  is_nixlf_attached (struct rvu*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npc_enable_mcam_entry (struct rvu*,struct npc_mcam*,int,size_t,int) ; 
 int /*<<< orphan*/  npc_mcam_clear_bit (struct npc_mcam*,size_t) ; 
 int /*<<< orphan*/  npc_mcam_free_all_entries (struct rvu*,struct npc_mcam*,int,scalar_t__) ; 
 int npc_mcam_verify_entry (struct npc_mcam*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  npc_unmap_mcam_entry_and_cntr (struct rvu*,struct npc_mcam*,int,size_t,scalar_t__) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rvu_mbox_handler_npc_mcam_free_entry(struct rvu *rvu,
					 struct npc_mcam_free_entry_req *req,
					 struct msg_rsp *rsp)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcifunc = req->hdr.pcifunc;
	int blkaddr, rc = 0;
	u16 cntr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return NPC_MCAM_INVALID_REQ;

	/* Free request from PFFUNC with no NIXLF attached, ignore */
	if (!is_nixlf_attached(rvu, pcifunc))
		return NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);

	if (req->all)
		goto free_all;

	rc = npc_mcam_verify_entry(mcam, pcifunc, req->entry);
	if (rc)
		goto exit;

	mcam->entry2pfvf_map[req->entry] = 0;
	npc_mcam_clear_bit(mcam, req->entry);
	npc_enable_mcam_entry(rvu, mcam, blkaddr, req->entry, false);

	/* Update entry2counter mapping */
	cntr = mcam->entry2cntr_map[req->entry];
	if (cntr != NPC_MCAM_INVALID_MAP)
		npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					      req->entry, cntr);

	goto exit;

free_all:
	/* Free up all entries allocated to requesting PFFUNC */
	npc_mcam_free_all_entries(rvu, mcam, blkaddr, pcifunc);
exit:
	mutex_unlock(&mcam->lock);
	return rc;
}