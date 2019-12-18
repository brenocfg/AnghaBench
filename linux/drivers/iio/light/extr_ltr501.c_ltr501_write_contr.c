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
struct ltr501_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTR501_ALS_CONTR ; 
 int /*<<< orphan*/  LTR501_PS_CONTR ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltr501_write_contr(struct ltr501_data *data, u8 als_val, u8 ps_val)
{
	int ret;

	ret = regmap_write(data->regmap, LTR501_ALS_CONTR, als_val);
	if (ret < 0)
		return ret;

	return regmap_write(data->regmap, LTR501_PS_CONTR, ps_val);
}