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
struct niu_ldg {int /*<<< orphan*/  irq; } ;
struct niu {int num_ldg; struct niu_ldg* ldg; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct niu_ldg*) ; 

__attribute__((used)) static void niu_free_irq(struct niu *np)
{
	int i;

	for (i = 0; i < np->num_ldg; i++) {
		struct niu_ldg *lp = &np->ldg[i];

		free_irq(lp->irq, lp);
	}
}