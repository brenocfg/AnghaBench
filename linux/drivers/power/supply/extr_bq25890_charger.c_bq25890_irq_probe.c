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
struct gpio_desc {int dummy; } ;
struct bq25890_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ25890_IRQ_PIN ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct gpio_desc* devm_gpiod_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiod_to_irq (struct gpio_desc*) ; 

__attribute__((used)) static int bq25890_irq_probe(struct bq25890_device *bq)
{
	struct gpio_desc *irq;

	irq = devm_gpiod_get(bq->dev, BQ25890_IRQ_PIN, GPIOD_IN);
	if (IS_ERR(irq)) {
		dev_err(bq->dev, "Could not probe irq pin.\n");
		return PTR_ERR(irq);
	}

	return gpiod_to_irq(irq);
}