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
struct TYPE_2__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_REG_IIR ; 
 int /*<<< orphan*/  QM_REG_ISR ; 
 TYPE_1__** affine_portals ; 
 int num_possible_cpus () ; 
 int /*<<< orphan*/  qm_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void qman_enable_irqs(void)
{
	int i;

	for (i = 0; i < num_possible_cpus(); i++) {
		if (affine_portals[i]) {
			qm_out(&affine_portals[i]->p, QM_REG_ISR, 0xffffffff);
			qm_out(&affine_portals[i]->p, QM_REG_IIR, 0);
		}

	}
}