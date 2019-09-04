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
struct tps80031 {int /*<<< orphan*/  irq_data; int /*<<< orphan*/ * regmap; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ TPS80031_INT_MSK_STS_A ; 
 size_t TPS80031_SLAVE_ID2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tps80031_irq_chip ; 
 int /*<<< orphan*/  tps80031_write (struct device*,size_t,scalar_t__,int) ; 

__attribute__((used)) static int tps80031_irq_init(struct tps80031 *tps80031, int irq, int irq_base)
{
	struct device *dev = tps80031->dev;
	int i, ret;

	/*
	 * The MASK register used for updating status register when
	 * interrupt occurs and LINE register used to pass the status
	 * to actual interrupt line.  As per datasheet:
	 * When INT_MSK_LINE [i] is set to 1, the associated interrupt
	 * number i is INT line masked, which means that no interrupt is
	 * generated on the INT line.
	 * When INT_MSK_LINE [i] is set to 0, the associated interrupt
	 * number i is  line enabled: An interrupt is generated on the
	 * INT line.
	 * In any case, the INT_STS [i] status bit may or may not be updated,
	 * only linked to the INT_MSK_STS [i] configuration register bit.
	 *
	 * When INT_MSK_STS [i] is set to 1, the associated interrupt number
	 * i is status masked, which means that no interrupt is stored in
	 * the INT_STS[i] status bit. Note that no interrupt number i is
	 * generated on the INT line, even if the INT_MSK_LINE [i] register
	 * bit is set to 0.
	 * When INT_MSK_STS [i] is set to 0, the associated interrupt number i
	 * is status enabled: An interrupt status is updated in the INT_STS [i]
	 * register. The interrupt may or may not be generated on the INT line,
	 * depending on the INT_MSK_LINE [i] configuration register bit.
	 */
	for (i = 0; i < 3; i++)
		tps80031_write(dev, TPS80031_SLAVE_ID2,
				TPS80031_INT_MSK_STS_A + i, 0x00);

	ret = regmap_add_irq_chip(tps80031->regmap[TPS80031_SLAVE_ID2], irq,
			IRQF_ONESHOT, irq_base,
			&tps80031_irq_chip, &tps80031->irq_data);
	if (ret < 0) {
		dev_err(dev, "add irq failed, err = %d\n", ret);
		return ret;
	}
	return ret;
}