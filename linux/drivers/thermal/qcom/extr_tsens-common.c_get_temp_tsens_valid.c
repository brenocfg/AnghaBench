#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct tsens_sensor {size_t hw_id; } ;
struct tsens_priv {TYPE_2__* fields; TYPE_1__* feat; int /*<<< orphan*/ * rf; struct tsens_sensor* sensor; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsb; int /*<<< orphan*/  msb; } ;
struct TYPE_3__ {scalar_t__ adc; } ;

/* Variables and functions */
 size_t GENMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t LAST_TEMP_0 ; 
 size_t VALID_0 ; 
 int code_to_degc (size_t,struct tsens_sensor*) ; 
 scalar_t__ fls (size_t) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int regmap_field_read (int /*<<< orphan*/ ,size_t*) ; 
 int sign_extend32 (size_t,scalar_t__) ; 

int get_temp_tsens_valid(struct tsens_priv *priv, int i, int *temp)
{
	struct tsens_sensor *s = &priv->sensor[i];
	u32 temp_idx = LAST_TEMP_0 + s->hw_id;
	u32 valid_idx = VALID_0 + s->hw_id;
	u32 last_temp = 0, valid, mask;
	int ret;

	ret = regmap_field_read(priv->rf[valid_idx], &valid);
	if (ret)
		return ret;
	while (!valid) {
		/* Valid bit is 0 for 6 AHB clock cycles.
		 * At 19.2MHz, 1 AHB clock is ~60ns.
		 * We should enter this loop very, very rarely.
		 */
		ndelay(400);
		ret = regmap_field_read(priv->rf[valid_idx], &valid);
		if (ret)
			return ret;
	}

	/* Valid bit is set, OK to read the temperature */
	ret = regmap_field_read(priv->rf[temp_idx], &last_temp);
	if (ret)
		return ret;

	if (priv->feat->adc) {
		/* Convert temperature from ADC code to milliCelsius */
		*temp = code_to_degc(last_temp, s) * 1000;
	} else {
		mask = GENMASK(priv->fields[LAST_TEMP_0].msb,
			       priv->fields[LAST_TEMP_0].lsb);
		/* Convert temperature from deciCelsius to milliCelsius */
		*temp = sign_extend32(last_temp, fls(mask) - 1) * 100;
	}

	return 0;
}