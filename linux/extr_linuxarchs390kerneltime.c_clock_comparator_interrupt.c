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
struct ext_code {int dummy; } ;
struct TYPE_2__ {scalar_t__ clock_comparator; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQEXT_CLK ; 
 TYPE_1__ S390_lowcore ; 
 scalar_t__ clock_comparator_max ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_clock_comparator (scalar_t__) ; 

__attribute__((used)) static void clock_comparator_interrupt(struct ext_code ext_code,
				       unsigned int param32,
				       unsigned long param64)
{
	inc_irq_stat(IRQEXT_CLK);
	if (S390_lowcore.clock_comparator == clock_comparator_max)
		set_clock_comparator(S390_lowcore.clock_comparator);
}