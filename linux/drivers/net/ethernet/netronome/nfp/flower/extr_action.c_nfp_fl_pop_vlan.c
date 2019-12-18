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
struct TYPE_2__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_pop_vlan {scalar_t__ reserved; TYPE_1__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_POP_VLAN ; 
 size_t NFP_FL_LW_SIZ ; 

__attribute__((used)) static void nfp_fl_pop_vlan(struct nfp_fl_pop_vlan *pop_vlan)
{
	size_t act_size = sizeof(struct nfp_fl_pop_vlan);

	pop_vlan->head.jump_id = NFP_FL_ACTION_OPCODE_POP_VLAN;
	pop_vlan->head.len_lw = act_size >> NFP_FL_LW_SIZ;
	pop_vlan->reserved = 0;
}