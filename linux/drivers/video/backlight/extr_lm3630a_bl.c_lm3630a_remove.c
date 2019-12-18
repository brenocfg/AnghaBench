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
struct lm3630a_chip {int /*<<< orphan*/  irqthread; scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BRT_A ; 
 int /*<<< orphan*/  REG_BRT_B ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct lm3630a_chip*) ; 
 struct lm3630a_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int lm3630a_write (struct lm3630a_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3630a_remove(struct i2c_client *client)
{
	int rval;
	struct lm3630a_chip *pchip = i2c_get_clientdata(client);

	rval = lm3630a_write(pchip, REG_BRT_A, 0);
	if (rval < 0)
		dev_err(pchip->dev, "i2c failed to access register\n");

	rval = lm3630a_write(pchip, REG_BRT_B, 0);
	if (rval < 0)
		dev_err(pchip->dev, "i2c failed to access register\n");

	if (pchip->irq) {
		free_irq(pchip->irq, pchip);
		flush_workqueue(pchip->irqthread);
		destroy_workqueue(pchip->irqthread);
	}
	return 0;
}