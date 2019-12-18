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
struct pnv_php_slot {int dummy; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int pnv_php_enable (struct pnv_php_slot*,int) ; 
 struct pnv_php_slot* to_pnv_php_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int pnv_php_enable_slot(struct hotplug_slot *slot)
{
	struct pnv_php_slot *php_slot = to_pnv_php_slot(slot);

	return pnv_php_enable(php_slot, true);
}