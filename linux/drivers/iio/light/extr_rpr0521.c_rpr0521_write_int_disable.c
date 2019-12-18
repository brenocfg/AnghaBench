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
struct rpr0521_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int RPR0521_INTERRUPT_INT_TRIG_ALS_DISABLE ; 
 int RPR0521_INTERRUPT_INT_TRIG_PS_DISABLE ; 
 int /*<<< orphan*/  RPR0521_REG_INTERRUPT ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rpr0521_write_int_disable(struct rpr0521_data *data)
{
	/* Don't care of clearing mode, assert and latch. */
	return regmap_write(data->regmap, RPR0521_REG_INTERRUPT,
				RPR0521_INTERRUPT_INT_TRIG_ALS_DISABLE |
				RPR0521_INTERRUPT_INT_TRIG_PS_DISABLE
				);
}