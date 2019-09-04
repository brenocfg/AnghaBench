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
typedef  int /*<<< orphan*/  u32 ;
struct bnxt {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_ROCE_MIRROR_CAP ; 
 int /*<<< orphan*/  VNIC_CFG_REQ_FLAGS_ROCE_DUAL_VNIC_MODE ; 
 int /*<<< orphan*/  VNIC_CFG_REQ_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_MODE ; 

__attribute__((used)) static u32 bnxt_get_roce_vnic_mode(struct bnxt *bp)
{
	if (bp->flags & BNXT_FLAG_ROCE_MIRROR_CAP)
		return VNIC_CFG_REQ_FLAGS_ROCE_MIRRORING_CAPABLE_VNIC_MODE;
	return VNIC_CFG_REQ_FLAGS_ROCE_DUAL_VNIC_MODE;
}