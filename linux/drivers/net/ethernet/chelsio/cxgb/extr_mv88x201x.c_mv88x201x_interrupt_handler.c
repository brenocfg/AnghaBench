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
struct cphy {int dummy; } ;

/* Variables and functions */
 int cphy_cause_link_change ; 
 int /*<<< orphan*/  mv88x201x_interrupt_clear (struct cphy*) ; 

__attribute__((used)) static int mv88x201x_interrupt_handler(struct cphy *cphy)
{
	/* Clear interrupts */
	mv88x201x_interrupt_clear(cphy);

	/* We have only enabled link change interrupts and so
	 * cphy_cause must be a link change interrupt.
	 */
	return cphy_cause_link_change;
}