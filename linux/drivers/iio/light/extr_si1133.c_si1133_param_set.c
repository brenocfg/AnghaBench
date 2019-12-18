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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct si1133_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int SI1133_CMD_PARAM_MASK ; 
 int SI1133_CMD_PARAM_SET ; 
 int /*<<< orphan*/  SI1133_REG_HOSTIN0 ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si1133_command (struct si1133_data*,int) ; 

__attribute__((used)) static int si1133_param_set(struct si1133_data *data, u8 param, u32 value)
{
	int err = regmap_write(data->regmap, SI1133_REG_HOSTIN0, value);

	if (err)
		return err;

	return si1133_command(data, SI1133_CMD_PARAM_SET |
			      (param & SI1133_CMD_PARAM_MASK));
}