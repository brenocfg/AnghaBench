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
struct rpr0521_data {int pxs_dev_en; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int RPR0521_MODE_PXS_MASK ; 
 int /*<<< orphan*/  RPR0521_REG_MODE_CTRL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rpr0521_pxs_enable(struct rpr0521_data *data, u8 status)
{
	int ret;

	ret = regmap_update_bits(data->regmap, RPR0521_REG_MODE_CTRL,
				 RPR0521_MODE_PXS_MASK,
				 status);
	if (ret < 0)
		return ret;

	if (status & RPR0521_MODE_PXS_MASK)
		data->pxs_dev_en = true;
	else
		data->pxs_dev_en = false;

	return 0;
}