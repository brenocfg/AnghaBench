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
typedef  int u16 ;
struct npc_mcam_alloc_entry_rsp {int count; int entry; int* entry_list; int free_count; } ;
struct npc_mcam_alloc_entry_req {scalar_t__ priority; int count; int ref_entry; scalar_t__ contig; } ;
struct npc_mcam {int bmap_fcnt; unsigned long* bmap; int lprio_start; int bmap_entries; int hprio_end; int lprio_count; unsigned long* bmap_reverse; int* entry2pfvf_map; int /*<<< orphan*/  lock; int /*<<< orphan*/ * entry2cntr_map; } ;

/* Variables and functions */
 int NPC_MAX_NONCONTIG_ENTRIES ; 
 int NPC_MCAM_ALLOC_FAILED ; 
 scalar_t__ NPC_MCAM_HIGHER_PRIO ; 
 int /*<<< orphan*/  NPC_MCAM_INVALID_MAP ; 
 scalar_t__ NPC_MCAM_LOWER_PRIO ; 
 int find_next_zero_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npc_get_mcam_search_range_priority (struct npc_mcam*,struct npc_mcam_alloc_entry_req*,int*,int*,int*) ; 
 int npc_mcam_find_zero_area (unsigned long*,int,int,int,int*) ; 
 int npc_mcam_get_free_count (unsigned long*,int,int) ; 
 int /*<<< orphan*/  npc_mcam_set_bit (struct npc_mcam*,int) ; 

__attribute__((used)) static int npc_mcam_alloc_entries(struct npc_mcam *mcam, u16 pcifunc,
				  struct npc_mcam_alloc_entry_req *req,
				  struct npc_mcam_alloc_entry_rsp *rsp)
{
	u16 entry_list[NPC_MAX_NONCONTIG_ENTRIES];
	u16 fcnt, hp_fcnt, lp_fcnt;
	u16 start, end, index;
	int entry, next_start;
	bool reverse = false;
	unsigned long *bmap;
	u16 max_contig;

	mutex_lock(&mcam->lock);

	/* Check if there are any free entries */
	if (!mcam->bmap_fcnt) {
		mutex_unlock(&mcam->lock);
		return NPC_MCAM_ALLOC_FAILED;
	}

	/* MCAM entries are divided into high priority, middle and
	 * low priority zones. Idea is to not allocate top and lower
	 * most entries as much as possible, this is to increase
	 * probability of honouring priority allocation requests.
	 *
	 * Two bitmaps are used for mcam entry management,
	 * mcam->bmap for forward search i.e '0 to mcam->bmap_entries'.
	 * mcam->bmap_reverse for reverse search i.e 'mcam->bmap_entries to 0'.
	 *
	 * Reverse bitmap is used to allocate entries
	 * - when a higher priority entry is requested
	 * - when available free entries are less.
	 * Lower priority ones out of avaialble free entries are always
	 * chosen when 'high vs low' question arises.
	 */

	/* Get the search range for priority allocation request */
	if (req->priority) {
		npc_get_mcam_search_range_priority(mcam, req,
						   &start, &end, &reverse);
		goto alloc;
	}

	/* Find out the search range for non-priority allocation request
	 *
	 * Get MCAM free entry count in middle zone.
	 */
	lp_fcnt = npc_mcam_get_free_count(mcam->bmap,
					  mcam->lprio_start,
					  mcam->bmap_entries);
	hp_fcnt = npc_mcam_get_free_count(mcam->bmap, 0, mcam->hprio_end);
	fcnt = mcam->bmap_fcnt - lp_fcnt - hp_fcnt;

	/* Check if request can be accomodated in the middle zone */
	if (fcnt > req->count) {
		start = mcam->hprio_end;
		end = mcam->lprio_start;
	} else if ((fcnt + (hp_fcnt / 2) + (lp_fcnt / 2)) > req->count) {
		/* Expand search zone from half of hprio zone to
		 * half of lprio zone.
		 */
		start = mcam->hprio_end / 2;
		end = mcam->bmap_entries - (mcam->lprio_count / 2);
		reverse = true;
	} else {
		/* Not enough free entries, search all entries in reverse,
		 * so that low priority ones will get used up.
		 */
		reverse = true;
		start = 0;
		end = mcam->bmap_entries;
	}

alloc:
	if (reverse) {
		bmap = mcam->bmap_reverse;
		start = mcam->bmap_entries - start;
		end = mcam->bmap_entries - end;
		index = start;
		start = end;
		end = index;
	} else {
		bmap = mcam->bmap;
	}

	if (req->contig) {
		/* Allocate requested number of contiguous entries, if
		 * unsuccessful find max contiguous entries available.
		 */
		index = npc_mcam_find_zero_area(bmap, end, start,
						req->count, &max_contig);
		rsp->count = max_contig;
		if (reverse)
			rsp->entry = mcam->bmap_entries - index - max_contig;
		else
			rsp->entry = index;
	} else {
		/* Allocate requested number of non-contiguous entries,
		 * if unsuccessful allocate as many as possible.
		 */
		rsp->count = 0;
		next_start = start;
		for (entry = 0; entry < req->count; entry++) {
			index = find_next_zero_bit(bmap, end, next_start);
			if (index >= end)
				break;

			next_start = start + (index - start) + 1;

			/* Save the entry's index */
			if (reverse)
				index = mcam->bmap_entries - index - 1;
			entry_list[entry] = index;
			rsp->count++;
		}
	}

	/* If allocating requested no of entries is unsucessful,
	 * expand the search range to full bitmap length and retry.
	 */
	if (!req->priority && (rsp->count < req->count) &&
	    ((end - start) != mcam->bmap_entries)) {
		reverse = true;
		start = 0;
		end = mcam->bmap_entries;
		goto alloc;
	}

	/* For priority entry allocation requests, if allocation is
	 * failed then expand search to max possible range and retry.
	 */
	if (req->priority && rsp->count < req->count) {
		if (req->priority == NPC_MCAM_LOWER_PRIO &&
		    (start != (req->ref_entry + 1))) {
			start = req->ref_entry + 1;
			end = mcam->bmap_entries;
			reverse = false;
			goto alloc;
		} else if ((req->priority == NPC_MCAM_HIGHER_PRIO) &&
			   ((end - start) != req->ref_entry)) {
			start = 0;
			end = req->ref_entry;
			reverse = true;
			goto alloc;
		}
	}

	/* Copy MCAM entry indices into mbox response entry_list.
	 * Requester always expects indices in ascending order, so
	 * so reverse the list if reverse bitmap is used for allocation.
	 */
	if (!req->contig && rsp->count) {
		index = 0;
		for (entry = rsp->count - 1; entry >= 0; entry--) {
			if (reverse)
				rsp->entry_list[index++] = entry_list[entry];
			else
				rsp->entry_list[entry] = entry_list[entry];
		}
	}

	/* Mark the allocated entries as used and set nixlf mapping */
	for (entry = 0; entry < rsp->count; entry++) {
		index = req->contig ?
			(rsp->entry + entry) : rsp->entry_list[entry];
		npc_mcam_set_bit(mcam, index);
		mcam->entry2pfvf_map[index] = pcifunc;
		mcam->entry2cntr_map[index] = NPC_MCAM_INVALID_MAP;
	}

	/* Update available free count in mbox response */
	rsp->free_count = mcam->bmap_fcnt;

	mutex_unlock(&mcam->lock);
	return 0;
}