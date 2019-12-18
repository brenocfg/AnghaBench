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

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_CFG (int) ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rvu_get_pf_numvfs(struct rvu *rvu, int pf, int *numvfs, int *hwvf)
{
	u64 cfg;

	/* Get numVFs attached to this PF and first HWVF */
	cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
	*numvfs = (cfg >> 12) & 0xFF;
	*hwvf = cfg & 0xFFF;
}