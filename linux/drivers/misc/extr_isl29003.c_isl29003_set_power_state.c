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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ISL29003_ADC_ENABLED ; 
 int ISL29003_ADC_PD ; 
 int /*<<< orphan*/  ISL29003_REG_COMMAND ; 
 int __isl29003_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isl29003_set_power_state(struct i2c_client *client, int state)
{
	return __isl29003_write_reg(client, ISL29003_REG_COMMAND,
				ISL29003_ADC_ENABLED | ISL29003_ADC_PD, 0,
				state ? ISL29003_ADC_ENABLED : ISL29003_ADC_PD);
}