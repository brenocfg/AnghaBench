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
struct i2c_client {scalar_t__ irq; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (scalar_t__) ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bma150_write_byte(struct i2c_client *client, u8 reg, u8 val)
{
	s32 ret;

	/* As per specification, disable irq in between register writes */
	if (client->irq)
		disable_irq_nosync(client->irq);

	ret = i2c_smbus_write_byte_data(client, reg, val);

	if (client->irq)
		enable_irq(client->irq);

	return ret;
}