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
struct ics {int dummy; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ OPAL_SUCCESS ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int XICS_IPI ; 
 unsigned int XICS_IRQ_SPURIOUS ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  ics_hal ; 
 int /*<<< orphan*/  ics_opal_irq_chip ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ opal_get_xive (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ virq_to_hw (unsigned int) ; 

__attribute__((used)) static int ics_opal_map(struct ics *ics, unsigned int virq)
{
	unsigned int hw_irq = (unsigned int)virq_to_hw(virq);
	int64_t rc;
	__be16 server;
	int8_t priority;

	if (WARN_ON(hw_irq == XICS_IPI || hw_irq == XICS_IRQ_SPURIOUS))
		return -EINVAL;

	/* Check if HAL knows about this interrupt */
	rc = opal_get_xive(hw_irq, &server, &priority);
	if (rc != OPAL_SUCCESS)
		return -ENXIO;

	irq_set_chip_and_handler(virq, &ics_opal_irq_chip, handle_fasteoi_irq);
	irq_set_chip_data(virq, &ics_hal);

	return 0;
}