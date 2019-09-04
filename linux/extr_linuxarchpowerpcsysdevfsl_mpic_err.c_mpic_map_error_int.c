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
struct mpic {int flags; scalar_t__* err_int_vecs; int /*<<< orphan*/  hc_err; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int MPIC_FSL_HAS_EIMR ; 
 int MPIC_MAX_ERR ; 
 int MPIC_SECONDARY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct mpic*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int mpic_map_error_int(struct mpic *mpic, unsigned int virq, irq_hw_number_t  hw)
{
	if ((mpic->flags & MPIC_FSL_HAS_EIMR) &&
	    (hw >= mpic->err_int_vecs[0] &&
	     hw <= mpic->err_int_vecs[MPIC_MAX_ERR - 1])) {
		WARN_ON(mpic->flags & MPIC_SECONDARY);

		pr_debug("mpic: mapping as Error Interrupt\n");
		irq_set_chip_data(virq, mpic);
		irq_set_chip_and_handler(virq, &mpic->hc_err,
					 handle_level_irq);
		return 1;
	}

	return 0;
}