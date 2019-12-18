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
struct cw1200_common {int /*<<< orphan*/  hw; int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __cw1200_irq_enable (struct cw1200_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_free_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_unregister_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void cw1200_core_release(struct cw1200_common *self)
{
	/* Disable device interrupts */
	self->hwbus_ops->lock(self->hwbus_priv);
	__cw1200_irq_enable(self, 0);
	self->hwbus_ops->unlock(self->hwbus_priv);

	/* And then clean up */
	cw1200_unregister_common(self->hw);
	cw1200_free_common(self->hw);
	return;
}