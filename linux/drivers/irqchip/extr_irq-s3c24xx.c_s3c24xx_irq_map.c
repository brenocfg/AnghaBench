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
struct s3c_irq_intc {int /*<<< orphan*/  domain; struct s3c_irq_data* irqs; int /*<<< orphan*/  reg_pending; struct s3c_irq_intc* parent; } ;
struct s3c_irq_data {size_t offset; int type; int parent_irq; unsigned long sub_bits; struct s3c_irq_intc* sub_intc; struct s3c_irq_intc* intc; } ;
struct irq_domain {struct s3c_irq_intc* host_data; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S3C2416_SRCPND2 ; 
#define  S3C_IRQTYPE_EDGE 131 
#define  S3C_IRQTYPE_EINT 130 
#define  S3C_IRQTYPE_LEVEL 129 
#define  S3C_IRQTYPE_NONE 128 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  irq_set_chained_handler (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct s3c_irq_data*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  s3c_irq_chip ; 
 int /*<<< orphan*/  s3c_irq_demux ; 
 int /*<<< orphan*/  s3c_irq_eint0t4 ; 
 int /*<<< orphan*/  s3c_irq_level_chip ; 
 int /*<<< orphan*/  s3c_irqext_chip ; 
 int /*<<< orphan*/  soc_is_s3c2412 () ; 

__attribute__((used)) static int s3c24xx_irq_map(struct irq_domain *h, unsigned int virq,
							irq_hw_number_t hw)
{
	struct s3c_irq_intc *intc = h->host_data;
	struct s3c_irq_data *irq_data = &intc->irqs[hw];
	struct s3c_irq_intc *parent_intc;
	struct s3c_irq_data *parent_irq_data;
	unsigned int irqno;

	/* attach controller pointer to irq_data */
	irq_data->intc = intc;
	irq_data->offset = hw;

	parent_intc = intc->parent;

	/* set handler and flags */
	switch (irq_data->type) {
	case S3C_IRQTYPE_NONE:
		return 0;
	case S3C_IRQTYPE_EINT:
		/* On the S3C2412, the EINT0to3 have a parent irq
		 * but need the s3c_irq_eint0t4 chip
		 */
		if (parent_intc && (!soc_is_s3c2412() || hw >= 4))
			irq_set_chip_and_handler(virq, &s3c_irqext_chip,
						 handle_edge_irq);
		else
			irq_set_chip_and_handler(virq, &s3c_irq_eint0t4,
						 handle_edge_irq);
		break;
	case S3C_IRQTYPE_EDGE:
		if (parent_intc || intc->reg_pending == S3C2416_SRCPND2)
			irq_set_chip_and_handler(virq, &s3c_irq_level_chip,
						 handle_edge_irq);
		else
			irq_set_chip_and_handler(virq, &s3c_irq_chip,
						 handle_edge_irq);
		break;
	case S3C_IRQTYPE_LEVEL:
		if (parent_intc)
			irq_set_chip_and_handler(virq, &s3c_irq_level_chip,
						 handle_level_irq);
		else
			irq_set_chip_and_handler(virq, &s3c_irq_chip,
						 handle_level_irq);
		break;
	default:
		pr_err("irq-s3c24xx: unsupported irqtype %d\n", irq_data->type);
		return -EINVAL;
	}

	irq_set_chip_data(virq, irq_data);

	if (parent_intc && irq_data->type != S3C_IRQTYPE_NONE) {
		if (irq_data->parent_irq > 31) {
			pr_err("irq-s3c24xx: parent irq %lu is out of range\n",
			       irq_data->parent_irq);
			return -EINVAL;
		}

		parent_irq_data = &parent_intc->irqs[irq_data->parent_irq];
		parent_irq_data->sub_intc = intc;
		parent_irq_data->sub_bits |= (1UL << hw);

		/* attach the demuxer to the parent irq */
		irqno = irq_find_mapping(parent_intc->domain,
					 irq_data->parent_irq);
		if (!irqno) {
			pr_err("irq-s3c24xx: could not find mapping for parent irq %lu\n",
			       irq_data->parent_irq);
			return -EINVAL;
		}
		irq_set_chained_handler(irqno, s3c_irq_demux);
	}

	return 0;
}