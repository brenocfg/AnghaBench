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
struct TYPE_2__ {scalar_t__ max; } ;
struct rvu_pfvf {TYPE_1__ msix; } ;
struct rvu {struct rvu_pfvf* pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 scalar_t__ RVU_AF_INT_VEC_CNT ; 
 scalar_t__ RVU_PF_INT_VEC_CNT ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_INT_CFG (int /*<<< orphan*/ ) ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvu_afvf_msix_vectors_num_ok(struct rvu *rvu)
{
	struct rvu_pfvf *pfvf = &rvu->pf[0];
	int offset;

	pfvf = &rvu->pf[0];
	offset = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_INT_CFG(0)) & 0x3ff;

	/* Make sure there are enough MSIX vectors configured so that
	 * VF interrupts can be handled. Offset equal to zero means
	 * that PF vectors are not configured and overlapping AF vectors.
	 */
	return (pfvf->msix.max >= RVU_AF_INT_VEC_CNT + RVU_PF_INT_VEC_CNT) &&
	       offset;
}