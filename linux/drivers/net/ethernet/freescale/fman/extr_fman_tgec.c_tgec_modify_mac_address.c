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
typedef  int /*<<< orphan*/  u8 ;
struct fman_mac {int /*<<< orphan*/  regs; int /*<<< orphan*/  addr; int /*<<< orphan*/  cfg; } ;
typedef  scalar_t__ enet_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENET_ADDR_TO_UINT64 (scalar_t__) ; 
 int /*<<< orphan*/  is_init_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int tgec_modify_mac_address(struct fman_mac *tgec, enet_addr_t *p_enet_addr)
{
	if (!is_init_done(tgec->cfg))
		return -EINVAL;

	tgec->addr = ENET_ADDR_TO_UINT64(*p_enet_addr);
	set_mac_address(tgec->regs, (u8 *)(*p_enet_addr));

	return 0;
}