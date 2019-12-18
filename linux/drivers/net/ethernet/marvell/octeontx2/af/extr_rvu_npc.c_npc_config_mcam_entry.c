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
typedef  int u8 ;
typedef  int u64 ;
struct rvu {int dummy; } ;
struct npc_mcam {int banksize; int banks_per_entry; } ;
struct mcam_entry {int action; int vtag_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_ACTION (int,int) ; 
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_CAMX_INTF (int,int,int) ; 
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_CAMX_W0 (int,int,int) ; 
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_CAMX_W1 (int,int,int) ; 
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_TAG_ACT (int,int) ; 
 int /*<<< orphan*/  npc_enable_mcam_entry (struct rvu*,struct npc_mcam*,int,int,int) ; 
 int npc_get_bank (struct npc_mcam*,int) ; 
 int /*<<< orphan*/  npc_get_keyword (struct mcam_entry*,int,int*,int*) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void npc_config_mcam_entry(struct rvu *rvu, struct npc_mcam *mcam,
				  int blkaddr, int index, u8 intf,
				  struct mcam_entry *entry, bool enable)
{
	int bank = npc_get_bank(mcam, index);
	int kw = 0, actbank, actindex;
	u64 cam0, cam1;

	actbank = bank; /* Save bank id, to set action later on */
	actindex = index;
	index &= (mcam->banksize - 1);

	/* CAM1 takes the comparison value and
	 * CAM0 specifies match for a bit in key being '0' or '1' or 'dontcare'.
	 * CAM1<n> = 0 & CAM0<n> = 1 => match if key<n> = 0
	 * CAM1<n> = 1 & CAM0<n> = 0 => match if key<n> = 1
	 * CAM1<n> = 0 & CAM0<n> = 0 => always match i.e dontcare.
	 */
	for (; bank < (actbank + mcam->banks_per_entry); bank++, kw = kw + 2) {
		/* Interface should be set in all banks */
		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 1),
			    intf);
		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_INTF(index, bank, 0),
			    ~intf & 0x3);

		/* Set the match key */
		npc_get_keyword(entry, kw, &cam0, &cam1);
		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 1), cam1);
		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W0(index, bank, 0), cam0);

		npc_get_keyword(entry, kw + 1, &cam0, &cam1);
		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 1), cam1);
		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CAMX_W1(index, bank, 0), cam0);
	}

	/* Set 'action' */
	rvu_write64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_ACTION(index, actbank), entry->action);

	/* Set TAG 'action' */
	rvu_write64(rvu, blkaddr, NPC_AF_MCAMEX_BANKX_TAG_ACT(index, actbank),
		    entry->vtag_action);

	/* Enable the entry */
	if (enable)
		npc_enable_mcam_entry(rvu, mcam, blkaddr, actindex, true);
	else
		npc_enable_mcam_entry(rvu, mcam, blkaddr, actindex, false);
}