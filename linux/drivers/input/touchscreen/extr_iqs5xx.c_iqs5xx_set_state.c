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
typedef  int /*<<< orphan*/  u8 ;
struct iqs5xx_private {scalar_t__ bl_status; int /*<<< orphan*/  lock; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ IQS5XX_BL_STATUS_RESET ; 
 int /*<<< orphan*/  IQS5XX_END_COMM ; 
 int /*<<< orphan*/  IQS5XX_SYS_CTRL1 ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct iqs5xx_private* i2c_get_clientdata (struct i2c_client*) ; 
 int iqs5xx_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iqs5xx_set_state(struct i2c_client *client, u8 state)
{
	struct iqs5xx_private *iqs5xx = i2c_get_clientdata(client);
	int error1, error2;

	if (iqs5xx->bl_status == IQS5XX_BL_STATUS_RESET)
		return 0;

	mutex_lock(&iqs5xx->lock);

	/*
	 * Addressing the device outside of a communication window prompts it
	 * to assert the RDY output, so disable the interrupt line to prevent
	 * the handler from servicing a false interrupt.
	 */
	disable_irq(client->irq);

	error1 = iqs5xx_write_byte(client, IQS5XX_SYS_CTRL1, state);
	error2 = iqs5xx_write_byte(client, IQS5XX_END_COMM, 0);

	usleep_range(50, 100);
	enable_irq(client->irq);

	mutex_unlock(&iqs5xx->lock);

	if (error1)
		return error1;

	return error2;
}