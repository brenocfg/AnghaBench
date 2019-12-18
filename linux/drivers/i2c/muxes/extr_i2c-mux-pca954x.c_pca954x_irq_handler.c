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
struct pca954x {int /*<<< orphan*/  irq; TYPE_1__* chip; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int nchans; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PCA954X_IRQ_OFFSET ; 
 int /*<<< orphan*/  handle_nested_irq (unsigned int) ; 
 int i2c_smbus_read_byte (int /*<<< orphan*/ ) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t pca954x_irq_handler(int irq, void *dev_id)
{
	struct pca954x *data = dev_id;
	unsigned int child_irq;
	int ret, i, handled = 0;

	ret = i2c_smbus_read_byte(data->client);
	if (ret < 0)
		return IRQ_NONE;

	for (i = 0; i < data->chip->nchans; i++) {
		if (ret & BIT(PCA954X_IRQ_OFFSET + i)) {
			child_irq = irq_linear_revmap(data->irq, i);
			handle_nested_irq(child_irq);
			handled++;
		}
	}
	return handled ? IRQ_HANDLED : IRQ_NONE;
}