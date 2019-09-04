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
struct i2c_versatile {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ I2C_CONTROL ; 
 int SDA ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int i2c_versatile_getsda(void *data)
{
	struct i2c_versatile *i2c = data;
	return !!(readl(i2c->base + I2C_CONTROL) & SDA);
}