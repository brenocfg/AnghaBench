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
typedef  int /*<<< orphan*/  phandle ;
struct TYPE_2__ {int /*<<< orphan*/  (* no_child ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  prom_lock ; 
 TYPE_1__* prom_nodeops ; 
 int /*<<< orphan*/  restore_current () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static phandle __prom_getchild(phandle node)
{
	unsigned long flags;
	phandle cnode;

	spin_lock_irqsave(&prom_lock, flags);
	cnode = prom_nodeops->no_child(node);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);

	return cnode;
}