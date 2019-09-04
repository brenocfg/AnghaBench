#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct its_vpe {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  has_direct_lpi; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_2__* gic_rdists ; 
 int /*<<< orphan*/  its_vpe_db_proxy_unmap_locked (struct its_vpe*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ vpe_proxy ; 

__attribute__((used)) static void its_vpe_db_proxy_unmap(struct its_vpe *vpe)
{
	if (!gic_rdists->has_direct_lpi) {
		unsigned long flags;

		raw_spin_lock_irqsave(&vpe_proxy.lock, flags);
		its_vpe_db_proxy_unmap_locked(vpe);
		raw_spin_unlock_irqrestore(&vpe_proxy.lock, flags);
	}
}