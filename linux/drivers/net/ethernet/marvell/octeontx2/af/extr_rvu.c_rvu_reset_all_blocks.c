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

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_CPT0 ; 
 int /*<<< orphan*/  BLKADDR_NDC0 ; 
 int /*<<< orphan*/  BLKADDR_NDC1 ; 
 int /*<<< orphan*/  BLKADDR_NDC2 ; 
 int /*<<< orphan*/  BLKADDR_NIX0 ; 
 int /*<<< orphan*/  BLKADDR_NPA ; 
 int /*<<< orphan*/  BLKADDR_NPC ; 
 int /*<<< orphan*/  BLKADDR_SSO ; 
 int /*<<< orphan*/  BLKADDR_TIM ; 
 int /*<<< orphan*/  CPT_AF_BLK_RST ; 
 int /*<<< orphan*/  NDC_AF_BLK_RST ; 
 int /*<<< orphan*/  NIX_AF_BLK_RST ; 
 int /*<<< orphan*/  NPA_AF_BLK_RST ; 
 int /*<<< orphan*/  NPC_AF_BLK_RST ; 
 int /*<<< orphan*/  SSO_AF_BLK_RST ; 
 int /*<<< orphan*/  TIM_AF_BLK_RST ; 
 int /*<<< orphan*/  rvu_block_reset (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvu_reset_all_blocks(struct rvu *rvu)
{
	/* Do a HW reset of all RVU blocks */
	rvu_block_reset(rvu, BLKADDR_NPA, NPA_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NIX0, NIX_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NPC, NPC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_SSO, SSO_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_TIM, TIM_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_CPT0, CPT_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC0, NDC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC1, NDC_AF_BLK_RST);
	rvu_block_reset(rvu, BLKADDR_NDC2, NDC_AF_BLK_RST);
}