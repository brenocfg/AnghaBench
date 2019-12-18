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
struct tpci200_board {struct tpci200_board* info; int /*<<< orphan*/  ipack_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipack_bus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tpci200_board*) ; 
 int /*<<< orphan*/  tpci200_uninstall (struct tpci200_board*) ; 

__attribute__((used)) static void __tpci200_pci_remove(struct tpci200_board *tpci200)
{
	ipack_bus_unregister(tpci200->info->ipack_bus);
	tpci200_uninstall(tpci200);

	kfree(tpci200->info);
	kfree(tpci200);
}