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
struct npc_mcam_shift_entry_rsp {size_t failed_entry_idx; } ;
struct TYPE_4__ {size_t pcifunc; } ;
struct npc_mcam_shift_entry_req {size_t shift_count; size_t* curr_entry; size_t* new_entry; TYPE_2__ hdr; } ;
struct npc_mcam {scalar_t__* entry2cntr_map; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 scalar_t__ NPC_MCAM_INVALID_MAP ; 
 int NPC_MCAM_INVALID_REQ ; 
 size_t NPC_MCAM_MAX_SHIFTS ; 
 int NPC_MCAM_PERM_DENIED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npc_copy_mcam_entry (struct rvu*,struct npc_mcam*,int,size_t,size_t) ; 
 int /*<<< orphan*/  npc_enable_mcam_entry (struct rvu*,struct npc_mcam*,int,size_t,int) ; 
 int /*<<< orphan*/  npc_map_mcam_entry_and_cntr (struct rvu*,struct npc_mcam*,int,size_t,size_t) ; 
 int npc_mcam_verify_entry (struct npc_mcam*,size_t,size_t) ; 
 int /*<<< orphan*/  npc_unmap_mcam_entry_and_cntr (struct rvu*,struct npc_mcam*,int,size_t,size_t) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rvu_mbox_handler_npc_mcam_shift_entry(struct rvu *rvu,
					  struct npc_mcam_shift_entry_req *req,
					  struct npc_mcam_shift_entry_rsp *rsp)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	u16 pcifunc = req->hdr.pcifunc;
	u16 old_entry, new_entry;
	u16 index, cntr;
	int blkaddr, rc;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return NPC_MCAM_INVALID_REQ;

	if (req->shift_count > NPC_MCAM_MAX_SHIFTS)
		return NPC_MCAM_INVALID_REQ;

	mutex_lock(&mcam->lock);
	for (index = 0; index < req->shift_count; index++) {
		old_entry = req->curr_entry[index];
		new_entry = req->new_entry[index];

		/* Check if both old and new entries are valid and
		 * does belong to this PFFUNC or not.
		 */
		rc = npc_mcam_verify_entry(mcam, pcifunc, old_entry);
		if (rc)
			break;

		rc = npc_mcam_verify_entry(mcam, pcifunc, new_entry);
		if (rc)
			break;

		/* new_entry should not have a counter mapped */
		if (mcam->entry2cntr_map[new_entry] != NPC_MCAM_INVALID_MAP) {
			rc = NPC_MCAM_PERM_DENIED;
			break;
		}

		/* Disable the new_entry */
		npc_enable_mcam_entry(rvu, mcam, blkaddr, new_entry, false);

		/* Copy rule from old entry to new entry */
		npc_copy_mcam_entry(rvu, mcam, blkaddr, old_entry, new_entry);

		/* Copy counter mapping, if any */
		cntr = mcam->entry2cntr_map[old_entry];
		if (cntr != NPC_MCAM_INVALID_MAP) {
			npc_unmap_mcam_entry_and_cntr(rvu, mcam, blkaddr,
						      old_entry, cntr);
			npc_map_mcam_entry_and_cntr(rvu, mcam, blkaddr,
						    new_entry, cntr);
		}

		/* Enable new_entry and disable old_entry */
		npc_enable_mcam_entry(rvu, mcam, blkaddr, new_entry, true);
		npc_enable_mcam_entry(rvu, mcam, blkaddr, old_entry, false);
	}

	/* If shift has failed then report the failed index */
	if (index != req->shift_count) {
		rc = NPC_MCAM_PERM_DENIED;
		rsp->failed_entry_idx = index;
	}

	mutex_unlock(&mcam->lock);
	return rc;
}