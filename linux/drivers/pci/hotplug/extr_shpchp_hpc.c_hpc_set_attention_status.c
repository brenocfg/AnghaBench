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
typedef  int u8 ;
struct slot {int /*<<< orphan*/  hp_slot; } ;

/* Variables and functions */
 int SET_ATTN_BLINK ; 
 int SET_ATTN_OFF ; 
 int SET_ATTN_ON ; 
 int shpc_write_cmd (struct slot*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hpc_set_attention_status(struct slot *slot, u8 value)
{
	u8 slot_cmd = 0;

	switch (value) {
		case 0:
			slot_cmd = SET_ATTN_OFF;	/* OFF */
			break;
		case 1:
			slot_cmd = SET_ATTN_ON;		/* ON */
			break;
		case 2:
			slot_cmd = SET_ATTN_BLINK;	/* BLINK */
			break;
		default:
			return -1;
	}

	return shpc_write_cmd(slot, slot->hp_slot, slot_cmd);
}