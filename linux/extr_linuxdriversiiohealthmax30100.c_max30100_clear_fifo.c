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
struct max30100_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30100_REG_FIFO_OVR_CTR ; 
 int /*<<< orphan*/  MAX30100_REG_FIFO_RD_PTR ; 
 int /*<<< orphan*/  MAX30100_REG_FIFO_WR_PTR ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max30100_clear_fifo(struct max30100_data *data)
{
	int ret;

	ret = regmap_write(data->regmap, MAX30100_REG_FIFO_WR_PTR, 0);
	if (ret)
		return ret;

	ret = regmap_write(data->regmap, MAX30100_REG_FIFO_OVR_CTR, 0);
	if (ret)
		return ret;

	return regmap_write(data->regmap, MAX30100_REG_FIFO_RD_PTR, 0);
}