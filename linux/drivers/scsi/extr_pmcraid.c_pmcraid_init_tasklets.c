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
struct pmcraid_instance {int num_hrrq; int /*<<< orphan*/ * hrrq_vector; int /*<<< orphan*/ * isr_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmcraid_tasklet_function ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pmcraid_init_tasklets(struct pmcraid_instance *pinstance)
{
	int i;
	for (i = 0; i < pinstance->num_hrrq; i++)
		tasklet_init(&pinstance->isr_tasklet[i],
			     pmcraid_tasklet_function,
			     (unsigned long)&pinstance->hrrq_vector[i]);
}