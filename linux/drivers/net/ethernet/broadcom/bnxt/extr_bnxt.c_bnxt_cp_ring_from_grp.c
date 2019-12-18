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
typedef  int /*<<< orphan*/  u16 ;
struct bnxt_ring_struct {size_t grp_idx; } ;
struct bnxt_ring_grp_info {int /*<<< orphan*/  cp_fw_ring_id; } ;
struct bnxt {struct bnxt_ring_grp_info* grp_info; } ;

/* Variables and functions */

__attribute__((used)) static u16 bnxt_cp_ring_from_grp(struct bnxt *bp, struct bnxt_ring_struct *ring)
{
	struct bnxt_ring_grp_info *grp_info;

	grp_info = &bp->grp_info[ring->grp_idx];
	return grp_info->cp_fw_ring_id;
}