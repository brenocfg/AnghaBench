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
struct rvu_pfvf {int dummy; } ;
struct rvu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int /*<<< orphan*/  NPC_AF_PKINDX_CPI_DEFX (int,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

void rvu_npc_set_pkind(struct rvu *rvu, int pkind, struct rvu_pfvf *pfvf)
{
	int blkaddr;
	u64 val = 0;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return;

	/* Config CPI base for the PKIND */
	val = pkind | 1ULL << 62;
	rvu_write64(rvu, blkaddr, NPC_AF_PKINDX_CPI_DEFX(pkind, 0), val);
}