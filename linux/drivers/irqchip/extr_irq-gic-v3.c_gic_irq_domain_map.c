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
struct irq_domain {int /*<<< orphan*/  host_data; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int EPERM ; 
#define  EPPI_RANGE 132 
#define  ESPI_RANGE 131 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
#define  LPI_RANGE 130 
#define  PPI_RANGE 129 
#define  SPI_RANGE 128 
 int __get_intid_range (int /*<<< orphan*/ ) ; 
 struct irq_chip gic_chip ; 
 int /*<<< orphan*/  gic_dist_supports_lpis () ; 
 struct irq_chip gic_eoimode1_chip ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  handle_percpu_devid_irq ; 
 int /*<<< orphan*/  irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,struct irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_percpu_devid (unsigned int) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  irqd_set_single_target (int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supports_deactivate_key ; 

__attribute__((used)) static int gic_irq_domain_map(struct irq_domain *d, unsigned int irq,
			      irq_hw_number_t hw)
{
	struct irq_chip *chip = &gic_chip;

	if (static_branch_likely(&supports_deactivate_key))
		chip = &gic_eoimode1_chip;

	switch (__get_intid_range(hw)) {
	case PPI_RANGE:
	case EPPI_RANGE:
		irq_set_percpu_devid(irq);
		irq_domain_set_info(d, irq, hw, chip, d->host_data,
				    handle_percpu_devid_irq, NULL, NULL);
		irq_set_status_flags(irq, IRQ_NOAUTOEN);
		break;

	case SPI_RANGE:
	case ESPI_RANGE:
		irq_domain_set_info(d, irq, hw, chip, d->host_data,
				    handle_fasteoi_irq, NULL, NULL);
		irq_set_probe(irq);
		irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(irq)));
		break;

	case LPI_RANGE:
		if (!gic_dist_supports_lpis())
			return -EPERM;
		irq_domain_set_info(d, irq, hw, chip, d->host_data,
				    handle_fasteoi_irq, NULL, NULL);
		break;

	default:
		return -EPERM;
	}

	return 0;
}