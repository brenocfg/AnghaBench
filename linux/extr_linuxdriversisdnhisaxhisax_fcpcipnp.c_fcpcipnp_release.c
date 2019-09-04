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
struct fritz_adapter {scalar_t__ io; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ AVM_STATUS0 ; 
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fritz_adapter*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void fcpcipnp_release(struct fritz_adapter *adapter)
{
	DBG(1, "");

	outb(0, adapter->io + AVM_STATUS0);
	free_irq(adapter->irq, adapter);
	release_region(adapter->io, 32);
}