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
typedef  size_t u16 ;
struct rvu {TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcifunc; } ;
struct npc_mcam_unmap_counter_req {size_t cntr; size_t entry; TYPE_2__ hdr; int /*<<< orphan*/  all; } ;
struct npc_mcam {size_t bmap_entries; size_t* entry2cntr_map; int /*<<< orphan*/  lock; int /*<<< orphan*/  bmap; int /*<<< orphan*/ * cntr_refcnt; } ;
struct msg_rsp {int dummy; } ;
struct TYPE_3__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int NPC_MCAM_INVALID_REQ ; 
 size_t find_next_bit (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int npc_mcam_verify_counter (struct npc_mcam*,int /*<<< orphan*/ ,size_t) ; 
 int npc_mcam_verify_entry (struct npc_mcam*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  npc_unmap_mcam_entry_and_cntr (struct rvu*,struct npc_mcam*,int,size_t,size_t) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rvu_mbox_handler_npc_mcam_unmap_counter(struct rvu *rvu,
		struct npc_mcam_unmap_counter_req *req, struct msg_rsp *rsp)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	u16 index, entry = 0;
	int blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	rc = npc_mcam_verify_counter(mcam, req->hdr.pcifunc, req->cntr);
	if (rc)
		goto exit;

	/* Unmap the MCAM entry and counter */
	if (!req->all) {
		rc = npc_mcam_verify_entry(mcam, req->hdr.pcifunc, req->entry);
		if (rc)
			goto exit;
		npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					      req->entry, req->cntr);
		goto exit;
	}

	/* Disable all MCAM entry's stats which are using this counter */
	while (entry < mcam->bmap_entries) {
		if (!mcam->cntr_refcnt[req->cntr])
			break;

		index = find_next_bit(mcam->bmap, mcam->bmap_entries, entry);
		if (index >= mcam->bmap_entries)
			break;
		if (mcam->entry2cntr_map[index] != req->cntr)
			continue;

		entry = index + 1;
		npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
					      index, req->cntr);
	}
exit:
	mutex_unlock(&mcam->lock);
	return rc;
}