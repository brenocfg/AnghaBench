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
struct bnxt {int flags; int fw_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_CHIP_TYPE_NITRO_A0 (struct bnxt*) ; 
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_NEW_RSS_CAP ; 
 int BNXT_FW_CAP_CFA_RFS_RING_TBL_IDX ; 
 scalar_t__ BNXT_PF (struct bnxt*) ; 

__attribute__((used)) static bool bnxt_rfs_supported(struct bnxt *bp)
{
	if (bp->flags & BNXT_FLAG_CHIP_P5) {
		if (bp->fw_cap & BNXT_FW_CAP_CFA_RFS_RING_TBL_IDX)
			return true;
		return false;
	}
	if (BNXT_PF(bp) && !BNXT_CHIP_TYPE_NITRO_A0(bp))
		return true;
	if (bp->flags & BNXT_FLAG_NEW_RSS_CAP)
		return true;
	return false;
}