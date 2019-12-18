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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ lm90_is_tripped (struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lm90_irq_thread(int irq, void *dev_id)
{
	struct i2c_client *client = dev_id;
	u16 status;

	if (lm90_is_tripped(client, &status))
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}