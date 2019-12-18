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
struct jz4780_i2c {int dummy; } ;

/* Variables and functions */
 int jz4780_i2c_enable (struct jz4780_i2c*) ; 
 int /*<<< orphan*/  jz4780_i2c_set_speed (struct jz4780_i2c*) ; 

__attribute__((used)) static int jz4780_i2c_prepare(struct jz4780_i2c *i2c)
{
	jz4780_i2c_set_speed(i2c);
	return jz4780_i2c_enable(i2c);
}