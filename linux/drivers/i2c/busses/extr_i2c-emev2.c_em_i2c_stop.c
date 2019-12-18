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
struct em_i2c_device {int dummy; } ;

/* Variables and functions */
 int I2C_BIT_SPIE0 ; 
 int I2C_BIT_SPT0 ; 
 int /*<<< orphan*/  I2C_OFS_IICC0 ; 
 int /*<<< orphan*/  em_clear_set_bit (struct em_i2c_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_i2c_wait_for_event (struct em_i2c_device*) ; 

__attribute__((used)) static void em_i2c_stop(struct em_i2c_device *priv)
{
	/* Send Stop condition */
	em_clear_set_bit(priv, 0, I2C_BIT_SPT0 | I2C_BIT_SPIE0, I2C_OFS_IICC0);

	/* Wait for stop condition */
	em_i2c_wait_for_event(priv);
}