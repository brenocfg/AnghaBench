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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct lv0104cs_private {size_t scale; size_t int_time; int /*<<< orphan*/  client; } ;
struct TYPE_4__ {int /*<<< orphan*/  regval; } ;
struct TYPE_3__ {int /*<<< orphan*/  regval; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LV0104CS_INTEG_100MS 134 
#define  LV0104CS_INTEG_12_5MS 133 
#define  LV0104CS_INTEG_200MS 132 
 int /*<<< orphan*/  LV0104CS_REGVAL_MEASURE ; 
 int /*<<< orphan*/  LV0104CS_REGVAL_SLEEP ; 
#define  LV0104CS_SCALE_0_25X 131 
#define  LV0104CS_SCALE_1X 130 
#define  LV0104CS_SCALE_2X 129 
#define  LV0104CS_SCALE_8X 128 
 TYPE_2__* lv0104cs_int_times ; 
 int lv0104cs_read_adc (int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* lv0104cs_scales ; 
 int lv0104cs_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lv0104cs_get_lux(struct lv0104cs_private *lv0104cs,
				int *val, int *val2)
{
	u8 regval = LV0104CS_REGVAL_MEASURE;
	u16 adc_output;
	int ret;

	regval |= lv0104cs_scales[lv0104cs->scale].regval;
	regval |= lv0104cs_int_times[lv0104cs->int_time].regval;
	ret = lv0104cs_write_reg(lv0104cs->client, regval);
	if (ret)
		return ret;

	/* wait for integration time to pass (with margin) */
	switch (lv0104cs->int_time) {
	case LV0104CS_INTEG_12_5MS:
		msleep(50);
		break;

	case LV0104CS_INTEG_100MS:
		msleep(150);
		break;

	case LV0104CS_INTEG_200MS:
		msleep(250);
		break;

	default:
		return -EINVAL;
	}

	ret = lv0104cs_read_adc(lv0104cs->client, &adc_output);
	if (ret)
		return ret;

	ret = lv0104cs_write_reg(lv0104cs->client, LV0104CS_REGVAL_SLEEP);
	if (ret)
		return ret;

	/* convert ADC output to lux */
	switch (lv0104cs->scale) {
	case LV0104CS_SCALE_0_25X:
		*val = adc_output * 4;
		*val2 = 0;
		return 0;

	case LV0104CS_SCALE_1X:
		*val = adc_output;
		*val2 = 0;
		return 0;

	case LV0104CS_SCALE_2X:
		*val = adc_output / 2;
		*val2 = (adc_output % 2) * 500000;
		return 0;

	case LV0104CS_SCALE_8X:
		*val = adc_output / 8;
		*val2 = (adc_output % 8) * 125000;
		return 0;

	default:
		return -EINVAL;
	}
}