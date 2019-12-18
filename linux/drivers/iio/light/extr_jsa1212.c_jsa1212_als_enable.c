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
struct jsa1212_data {int als_en; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSA1212_CONF_ALS_MASK ; 
 int /*<<< orphan*/  JSA1212_CONF_REG ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jsa1212_als_enable(struct jsa1212_data *data, u8 status)
{
	int ret;

	ret = regmap_update_bits(data->regmap, JSA1212_CONF_REG,
				JSA1212_CONF_ALS_MASK,
				status);
	if (ret < 0)
		return ret;

	data->als_en = !!status;

	return 0;
}