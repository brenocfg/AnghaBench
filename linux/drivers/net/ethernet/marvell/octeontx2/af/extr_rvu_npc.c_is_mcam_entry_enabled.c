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
typedef  int u64 ;
struct rvu {int dummy; } ;
struct npc_mcam {int banksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_CFG (int,int) ; 
 int npc_get_bank (struct npc_mcam*,int) ; 
 int rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_mcam_entry_enabled(struct rvu *rvu, struct npc_mcam *mcam,
				  int blkaddr, int index)
{
	int bank = npc_get_bank(mcam, index);
	u64 cfg;

	index &= (mcam->banksize - 1);
	cfg = rvu_read64(rvu, blkaddr, NPC_AF_MCAMEX_BANKX_CFG(index, bank));
	return (cfg & 1);
}