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
struct slot {int /*<<< orphan*/  presence_save; TYPE_1__* hpc_ops; int /*<<< orphan*/  latch_save; int /*<<< orphan*/  attention_save; int /*<<< orphan*/  pwr_save; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_adapter_status ) (struct slot*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_latch_status ) (struct slot*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_attention_status ) (struct slot*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_power_status ) (struct slot*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct slot*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_slot_info(struct slot *slot)
{
	slot->hpc_ops->get_power_status(slot, &slot->pwr_save);
	slot->hpc_ops->get_attention_status(slot, &slot->attention_save);
	slot->hpc_ops->get_latch_status(slot, &slot->latch_save);
	slot->hpc_ops->get_adapter_status(slot, &slot->presence_save);
}