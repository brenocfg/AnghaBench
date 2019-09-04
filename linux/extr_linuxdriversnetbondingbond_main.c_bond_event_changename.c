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
struct bonding {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  bond_create_proc_entry (struct bonding*) ; 
 int /*<<< orphan*/  bond_debug_reregister (struct bonding*) ; 
 int /*<<< orphan*/  bond_remove_proc_entry (struct bonding*) ; 

__attribute__((used)) static int bond_event_changename(struct bonding *bond)
{
	bond_remove_proc_entry(bond);
	bond_create_proc_entry(bond);

	bond_debug_reregister(bond);

	return NOTIFY_DONE;
}