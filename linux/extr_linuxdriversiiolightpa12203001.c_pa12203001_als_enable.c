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
struct pa12203001_data {int als_enabled; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  PA12203001_ALS_EN_MASK ; 
 int /*<<< orphan*/  PA12203001_REG_CFG0 ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pa12203001_als_enable(struct pa12203001_data *data, u8 enable)
{
	int ret;

	ret = regmap_update_bits(data->map, PA12203001_REG_CFG0,
				 PA12203001_ALS_EN_MASK, enable);
	if (ret < 0)
		return ret;

	data->als_enabled = !!enable;

	return 0;
}