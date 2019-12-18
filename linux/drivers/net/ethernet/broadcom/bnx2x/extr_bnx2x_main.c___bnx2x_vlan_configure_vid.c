#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {TYPE_2__* fp; TYPE_1__* sp_objs; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_obj; } ;

/* Variables and functions */
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int bnx2x_set_vlan_one (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned long*) ; 
 int bnx2x_vfpf_update_vlan (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __bnx2x_vlan_configure_vid(struct bnx2x *bp, u16 vid, bool add)
{
	int rc;

	if (IS_PF(bp)) {
		unsigned long ramrod_flags = 0;

		__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
		rc = bnx2x_set_vlan_one(bp, vid, &bp->sp_objs->vlan_obj,
					add, &ramrod_flags);
	} else {
		rc = bnx2x_vfpf_update_vlan(bp, vid, bp->fp->index, add);
	}

	return rc;
}