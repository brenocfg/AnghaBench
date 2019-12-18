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
typedef  scalar_t__ u16 ;
struct npc_mcam_alloc_entry_req {scalar_t__ priority; scalar_t__ ref_entry; scalar_t__ count; } ;
struct npc_mcam {scalar_t__ bmap_entries; scalar_t__ hprio_end; scalar_t__ lprio_start; int /*<<< orphan*/  bmap; } ;

/* Variables and functions */
 scalar_t__ NPC_MCAM_HIGHER_PRIO ; 
 scalar_t__ npc_mcam_get_free_count (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
npc_get_mcam_search_range_priority(struct npc_mcam *mcam,
				   struct npc_mcam_alloc_entry_req *req,
				   u16 *start, u16 *end, bool *reverse)
{
	u16 fcnt;

	if (req->priority == NPC_MCAM_HIGHER_PRIO)
		goto hprio;

	/* For a low priority entry allocation
	 * - If reference entry is not in hprio zone then
	 *      search range: ref_entry to end.
	 * - If reference entry is in hprio zone and if
	 *   request can be accomodated in non-hprio zone then
	 *      search range: 'start of middle zone' to 'end'
	 * - else search in reverse, so that less number of hprio
	 *   zone entries are allocated.
	 */

	*reverse = false;
	*start = req->ref_entry + 1;
	*end = mcam->bmap_entries;

	if (req->ref_entry >= mcam->hprio_end)
		return;

	fcnt = npc_mcam_get_free_count(mcam->bmap,
				       mcam->hprio_end, mcam->bmap_entries);
	if (fcnt > req->count)
		*start = mcam->hprio_end;
	else
		*reverse = true;
	return;

hprio:
	/* For a high priority entry allocation, search is always
	 * in reverse to preserve hprio zone entries.
	 * - If reference entry is not in lprio zone then
	 *      search range: 0 to ref_entry.
	 * - If reference entry is in lprio zone and if
	 *   request can be accomodated in middle zone then
	 *      search range: 'hprio_end' to 'lprio_start'
	 */

	*reverse = true;
	*start = 0;
	*end = req->ref_entry;

	if (req->ref_entry <= mcam->lprio_start)
		return;

	fcnt = npc_mcam_get_free_count(mcam->bmap,
				       mcam->hprio_end, mcam->lprio_start);
	if (fcnt < req->count)
		return;
	*start = mcam->hprio_end;
	*end = mcam->lprio_start;
}