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

/* Variables and functions */
 int /*<<< orphan*/  T1_IRQMASTER ; 
 int /*<<< orphan*/  t1outp (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void t1_disable_irq(unsigned int base)
{
	t1outp(base, T1_IRQMASTER, 0x00);
}