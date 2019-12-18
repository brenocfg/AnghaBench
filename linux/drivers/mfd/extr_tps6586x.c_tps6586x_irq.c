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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u32 ;
struct tps6586x {int irq_en; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  acks ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  TPS6586X_INT_ACK1 ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  handle_nested_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int) ; 
 int tps6586x_reads (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tps6586x_irq(int irq, void *data)
{
	struct tps6586x *tps6586x = data;
	u32 acks;
	int ret = 0;

	ret = tps6586x_reads(tps6586x->dev, TPS6586X_INT_ACK1,
			     sizeof(acks), (uint8_t *)&acks);

	if (ret < 0) {
		dev_err(tps6586x->dev, "failed to read interrupt status\n");
		return IRQ_NONE;
	}

	acks = le32_to_cpu(acks);

	while (acks) {
		int i = __ffs(acks);

		if (tps6586x->irq_en & (1 << i))
			handle_nested_irq(
				irq_find_mapping(tps6586x->irq_domain, i));

		acks &= ~(1 << i);
	}

	return IRQ_HANDLED;
}