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
 int RPR0521_INTERRUPT_ALS_INT_STATUS_MASK ; 
 int RPR0521_INTERRUPT_PS_INT_STATUS_MASK ; 
 int /*<<< orphan*/  RPR0521_REG_INTERRUPT ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline bool rpr0521_is_triggered(struct rpr0521_data *data)
{
	int ret;
	int reg;

	ret = regmap_read(data->regmap, RPR0521_REG_INTERRUPT, &reg);
	if (ret < 0)
		return false;   /* Reg read failed. */
	if (reg &
	    (RPR0521_INTERRUPT_ALS_INT_STATUS_MASK |
	    RPR0521_INTERRUPT_PS_INT_STATUS_MASK))
		return true;
	else
		return false;   /* Int not from this sensor. */
}