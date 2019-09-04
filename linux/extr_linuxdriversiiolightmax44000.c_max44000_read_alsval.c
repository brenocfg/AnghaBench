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
typedef  int /*<<< orphan*/  val ;
typedef  int u16 ;
struct max44000_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int MAX44000_ALSDATA_OVERFLOW ; 
 int MAX44000_ALSTIM_SHIFT (int) ; 
 int /*<<< orphan*/  MAX44000_REG_ALS_DATA_HI ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int max44000_read_alstim (struct max44000_data*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int max44000_read_alsval(struct max44000_data *data)
{
	u16 regval;
	__be16 val;
	int alstim, ret;

	ret = regmap_bulk_read(data->regmap, MAX44000_REG_ALS_DATA_HI,
			       &val, sizeof(val));
	if (ret < 0)
		return ret;
	alstim = ret = max44000_read_alstim(data);
	if (ret < 0)
		return ret;

	regval = be16_to_cpu(val);

	/*
	 * Overflow is explained on datasheet page 17.
	 *
	 * It's a warning that either the G or IR channel has become saturated
	 * and that the value in the register is likely incorrect.
	 *
	 * The recommendation is to change the scale (ALSPGA).
	 * The driver just returns the max representable value.
	 */
	if (regval & MAX44000_ALSDATA_OVERFLOW)
		return 0x3FFF;

	return regval << MAX44000_ALSTIM_SHIFT(alstim);
}