#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u16 ;
struct rvu {TYPE_1__* hw; } ;
struct TYPE_2__ {int total_pfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 int RVU_PFVF_FUNC_MASK ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_CFG (int) ; 
 int rvu_get_pf (int) ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_pf_func_valid(struct rvu *rvu, u16 pcifunc)
{
	int pf, vf, nvfs;
	u64 cfg;

	pf = rvu_get_pf(pcifunc);
	if (pf >= rvu->hw->total_pfs)
		return false;

	if (!(pcifunc & RVU_PFVF_FUNC_MASK))
		return true;

	/* Check if VF is within number of VFs attached to this PF */
	vf = (pcifunc & RVU_PFVF_FUNC_MASK) - 1;
	cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
	nvfs = (cfg >> 12) & 0xFF;
	if (vf >= nvfs)
		return false;

	return true;
}