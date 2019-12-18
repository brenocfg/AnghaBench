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
typedef  unsigned int u8 ;
struct tqmx86_gpio_data {unsigned int* irq_type; int /*<<< orphan*/  spinlock; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQF_TRIGGER_MASK ; 
#define  IRQ_TYPE_EDGE_BOTH 130 
#define  IRQ_TYPE_EDGE_FALLING 129 
#define  IRQ_TYPE_EDGE_RISING 128 
 int /*<<< orphan*/  TQMX86_GPIIC ; 
 unsigned int TQMX86_GPII_BITS ; 
 unsigned int TQMX86_GPII_FALLING ; 
 unsigned int TQMX86_GPII_MASK ; 
 unsigned int TQMX86_GPII_RISING ; 
 unsigned int TQMX86_NGPO ; 
 struct tqmx86_gpio_data* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int tqmx86_gpio_read (struct tqmx86_gpio_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tqmx86_gpio_write (struct tqmx86_gpio_data*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tqmx86_gpio_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct tqmx86_gpio_data *gpio = gpiochip_get_data(
		irq_data_get_irq_chip_data(data));
	unsigned int offset = (data->hwirq - TQMX86_NGPO);
	unsigned int edge_type = type & IRQF_TRIGGER_MASK;
	unsigned long flags;
	u8 new_type, gpiic;

	switch (edge_type) {
	case IRQ_TYPE_EDGE_RISING:
		new_type = TQMX86_GPII_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		new_type = TQMX86_GPII_FALLING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		new_type = TQMX86_GPII_FALLING | TQMX86_GPII_RISING;
		break;
	default:
		return -EINVAL; /* not supported */
	}

	gpio->irq_type[offset] = new_type;

	raw_spin_lock_irqsave(&gpio->spinlock, flags);
	gpiic = tqmx86_gpio_read(gpio, TQMX86_GPIIC);
	gpiic &= ~((TQMX86_GPII_MASK) << (offset * TQMX86_GPII_BITS));
	gpiic |= new_type << (offset * TQMX86_GPII_BITS);
	tqmx86_gpio_write(gpio, gpiic, TQMX86_GPIIC);
	raw_spin_unlock_irqrestore(&gpio->spinlock, flags);

	return 0;
}