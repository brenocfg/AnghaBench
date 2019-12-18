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
struct icside_state {scalar_t__ ioc_base; } ;
struct expansion_card {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irqdisable ) (struct expansion_card*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct icside_state* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct expansion_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void icside_shutdown(struct expansion_card *ec)
{
	struct icside_state *state = ecard_get_drvdata(ec);
	unsigned long flags;

	/*
	 * Disable interrupts from this card.  We need to do
	 * this before disabling EASI since we may be accessing
	 * this register via that region.
	 */
	local_irq_save(flags);
	ec->ops->irqdisable(ec, 0);
	local_irq_restore(flags);

	/*
	 * Reset the ROM pointer so that we can read the ROM
	 * after a soft reboot.  This also disables access to
	 * the IDE taskfile via the EASI region.
	 */
	if (state->ioc_base)
		writeb(0, state->ioc_base);
}