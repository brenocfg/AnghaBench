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
struct max14577 {int /*<<< orphan*/  i2c_pmic; int /*<<< orphan*/  irq_data_pmic; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max77836_remove(struct max14577 *max14577)
{
	regmap_del_irq_chip(max14577->irq, max14577->irq_data_pmic);
	i2c_unregister_device(max14577->i2c_pmic);
}