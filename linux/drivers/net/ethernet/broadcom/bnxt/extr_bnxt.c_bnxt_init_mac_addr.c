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
struct bnxt_vf_info {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac_addr; } ;
struct bnxt {TYPE_2__* dev; struct bnxt_vf_info vf; TYPE_1__ pf; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int bnxt_approve_mac (struct bnxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_2__*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_init_mac_addr(struct bnxt *bp)
{
	int rc = 0;

	if (BNXT_PF(bp)) {
		memcpy(bp->dev->dev_addr, bp->pf.mac_addr, ETH_ALEN);
	} else {
#ifdef CONFIG_BNXT_SRIOV
		struct bnxt_vf_info *vf = &bp->vf;
		bool strict_approval = true;

		if (is_valid_ether_addr(vf->mac_addr)) {
			/* overwrite netdev dev_addr with admin VF MAC */
			memcpy(bp->dev->dev_addr, vf->mac_addr, ETH_ALEN);
			/* Older PF driver or firmware may not approve this
			 * correctly.
			 */
			strict_approval = false;
		} else {
			eth_hw_addr_random(bp->dev);
		}
		rc = bnxt_approve_mac(bp, bp->dev->dev_addr, strict_approval);
#endif
	}
	return rc;
}