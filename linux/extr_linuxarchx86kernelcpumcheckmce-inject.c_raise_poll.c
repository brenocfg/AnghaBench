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
struct mce {scalar_t__ finished; } ;
typedef  int /*<<< orphan*/  mce_banks_t ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  machine_check_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void raise_poll(struct mce *m)
{
	unsigned long flags;
	mce_banks_t b;

	memset(&b, 0xff, sizeof(mce_banks_t));
	local_irq_save(flags);
	machine_check_poll(0, &b);
	local_irq_restore(flags);
	m->finished = 0;
}