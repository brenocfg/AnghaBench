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
struct slot {int /*<<< orphan*/  hp_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_PWR_BLINK ; 
 int /*<<< orphan*/  shpc_write_cmd (struct slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpc_set_green_led_blink(struct slot *slot)
{
	shpc_write_cmd(slot, slot->hp_slot, SET_PWR_BLINK);
}