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
typedef  scalar_t__ u8 ;
struct slot {scalar_t__ device; } ;
struct controller {scalar_t__ slot_device_offset; } ;

/* Variables and functions */
 int read_amber_LED (struct controller*,scalar_t__) ; 

__attribute__((used)) static inline int cpq_get_attention_status(struct controller *ctrl, struct slot *slot)
{
	u8 hp_slot;

	hp_slot = slot->device - ctrl->slot_device_offset;

	return read_amber_LED(ctrl, hp_slot);
}