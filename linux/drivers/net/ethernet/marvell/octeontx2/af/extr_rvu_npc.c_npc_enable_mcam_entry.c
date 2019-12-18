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
struct rvu {int dummy; } ;
struct npc_mcam {int banksize; int banks_per_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_CFG (int,int) ; 
 int npc_get_bank (struct npc_mcam*,int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void npc_enable_mcam_entry(struct rvu *rvu, struct npc_mcam *mcam,
				  int blkaddr, int index, bool enable)
{
	int bank = npc_get_bank(mcam, index);
	int actbank = bank;

	index &= (mcam->banksize - 1);
	for (; bank < (actbank + mcam->banks_per_entry); bank++) {
		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_CFG(index, bank),
			    enable ? 1 : 0);
	}
}