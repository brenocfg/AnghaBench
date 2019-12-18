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
struct TYPE_2__ {int /*<<< orphan*/  vlan; } ;
struct bnxt {TYPE_1__ vf; } ;

/* Variables and functions */
 scalar_t__ BNXT_VF (struct bnxt*) ; 

__attribute__((used)) static bool bnxt_promisc_ok(struct bnxt *bp)
{
#ifdef CONFIG_BNXT_SRIOV
	if (BNXT_VF(bp) && !bp->vf.vlan)
		return false;
#endif
	return true;
}