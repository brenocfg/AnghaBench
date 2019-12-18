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
struct rvu {int dummy; } ;
struct npc_mcam {int banksize; int /*<<< orphan*/ * cntr_refcnt; int /*<<< orphan*/ * entry2cntr_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_STAT_ACT (int,int) ; 
 int /*<<< orphan*/  NPC_MCAM_INVALID_MAP ; 
 int npc_get_bank (struct npc_mcam*,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void npc_unmap_mcam_entry_and_cntr(struct rvu *rvu,
					  struct npc_mcam *mcam,
					  int blkaddr, u16 entry, u16 cntr)
{
	u16 index = entry & (mcam->banksize - 1);
	u16 bank = npc_get_bank(mcam, entry);

	/* Remove mapping and reduce counter's refcnt */
	mcam->entry2cntr_map[entry] = NPC_MCAM_INVALID_MAP;
	mcam->cntr_refcnt[cntr]--;
	/* Disable stats */
	rvu_write64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_STAT_ACT(index, bank), 0x00);
}