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
typedef  int /*<<< orphan*/  u8 ;
struct qed_hwfn {TYPE_1__* vf_iov_info; } ;
struct qed_bulletin_content {int valid_bitmap; int /*<<< orphan*/  mac; } ;
struct TYPE_2__ {struct qed_bulletin_content bulletin_shadow; } ;

/* Variables and functions */
 int MAC_ADDR_FORCED ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool qed_vf_check_mac(struct qed_hwfn *p_hwfn, u8 *mac)
{
	struct qed_bulletin_content *bulletin;

	bulletin = &p_hwfn->vf_iov_info->bulletin_shadow;
	if (!(bulletin->valid_bitmap & (1 << MAC_ADDR_FORCED)))
		return true;

	/* Forbid VF from changing a MAC enforced by PF */
	if (ether_addr_equal(bulletin->mac, mac))
		return false;

	return false;
}