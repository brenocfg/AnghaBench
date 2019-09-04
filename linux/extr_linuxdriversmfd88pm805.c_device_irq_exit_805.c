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
struct pm80x_chip {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_irq_exit_805(struct pm80x_chip *chip)
{
	regmap_del_irq_chip(chip->irq, chip->irq_data);
}