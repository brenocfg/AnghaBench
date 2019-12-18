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
struct irte {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQ_ALL_16 ; 
 int /*<<< orphan*/  SVT_VERIFY_BUS ; 
 int /*<<< orphan*/  set_irte_sid (struct irte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void set_irte_verify_bus(struct irte *irte, unsigned int start_bus,
				unsigned int end_bus)
{
	set_irte_sid(irte, SVT_VERIFY_BUS, SQ_ALL_16,
		     (start_bus << 8) | end_bus);
}