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
struct bna_enet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_enet_mtu_cbfn (struct bna_enet*) ; 

__attribute__((used)) static void
bna_enet_sm_started_entry(struct bna_enet *enet)
{
	/**
	 * NOTE: Do not call bna_enet_chld_start() here, since it will be
	 * inadvertently called during cfg_wait->started transition as well
	 */
	call_enet_mtu_cbfn(enet);
}