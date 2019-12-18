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
struct TYPE_3__ {int /*<<< orphan*/  r; } ;
struct TYPE_4__ {TYPE_1__ intr; } ;

/* Variables and functions */
 TYPE_2__* adb ; 
 scalar_t__ in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  macio_adb_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void macio_adb_poll(void)
{
	unsigned long flags;

	local_irq_save(flags);
	if (in_8(&adb->intr.r) != 0)
		macio_adb_interrupt(0, NULL);
	local_irq_restore(flags);
}