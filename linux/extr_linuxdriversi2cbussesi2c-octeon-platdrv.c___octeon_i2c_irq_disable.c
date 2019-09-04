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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 

__attribute__((used)) static void __octeon_i2c_irq_disable(atomic_t *cnt, int irq)
{
	int count;

	/*
	 * The interrupt can be disabled in two places, but we only
	 * want to make the disable_irq_nosync() call once, so keep
	 * track with the atomic variable.
	 */
	count = atomic_dec_if_positive(cnt);
	if (count >= 0)
		disable_irq_nosync(irq);
}