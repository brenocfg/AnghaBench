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
struct pnv_php_slot {int /*<<< orphan*/  attention_state; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 struct pnv_php_slot* to_pnv_php_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int pnv_php_get_attention_state(struct hotplug_slot *slot, u8 *state)
{
	struct pnv_php_slot *php_slot = to_pnv_php_slot(slot);

	*state = php_slot->attention_state;
	return 0;
}