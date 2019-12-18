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
struct vcnl4035_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int VCNL4035_INT_ALS_IF_H_MASK ; 
 int VCNL4035_INT_ALS_IF_L_MASK ; 
 int /*<<< orphan*/  VCNL4035_INT_FLAG ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline bool vcnl4035_is_triggered(struct vcnl4035_data *data)
{
	int ret;
	int reg;

	ret = regmap_read(data->regmap, VCNL4035_INT_FLAG, &reg);
	if (ret < 0)
		return false;

	return !!(reg &
		(VCNL4035_INT_ALS_IF_H_MASK | VCNL4035_INT_ALS_IF_L_MASK));
}