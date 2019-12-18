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
struct noa1305_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_VAL_FRACTIONAL ; 
#define  NOA1305_INTEGR_TIME_100MS 135 
#define  NOA1305_INTEGR_TIME_12_5MS 134 
#define  NOA1305_INTEGR_TIME_200MS 133 
#define  NOA1305_INTEGR_TIME_25MS 132 
#define  NOA1305_INTEGR_TIME_400MS 131 
#define  NOA1305_INTEGR_TIME_50MS 130 
#define  NOA1305_INTEGR_TIME_6_25MS 129 
#define  NOA1305_INTEGR_TIME_800MS 128 
 int /*<<< orphan*/  NOA1305_REG_INTEGRATION_TIME ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int noa1305_scale(struct noa1305_priv *priv, int *val, int *val2)
{
	int data;
	int ret;

	ret = regmap_read(priv->regmap, NOA1305_REG_INTEGRATION_TIME, &data);
	if (ret < 0)
		return ret;

	/*
	 * Lux = count / (<Integration Constant> * <Integration Time>)
	 *
	 * Integration Constant = 7.7
	 * Integration Time in Seconds
	 */
	switch (data) {
	case NOA1305_INTEGR_TIME_800MS:
		*val = 100;
		*val2 = 77 * 8;
		break;
	case NOA1305_INTEGR_TIME_400MS:
		*val = 100;
		*val2 = 77 * 4;
		break;
	case NOA1305_INTEGR_TIME_200MS:
		*val = 100;
		*val2 = 77 * 2;
		break;
	case NOA1305_INTEGR_TIME_100MS:
		*val = 100;
		*val2 = 77;
		break;
	case NOA1305_INTEGR_TIME_50MS:
		*val = 1000;
		*val2 = 77 * 5;
		break;
	case NOA1305_INTEGR_TIME_25MS:
		*val = 10000;
		*val2 = 77 * 25;
		break;
	case NOA1305_INTEGR_TIME_12_5MS:
		*val = 100000;
		*val2 = 77 * 125;
		break;
	case NOA1305_INTEGR_TIME_6_25MS:
		*val = 1000000;
		*val2 = 77 * 625;
		break;
	default:
		return -EINVAL;
	}

	return IIO_VAL_FRACTIONAL;
}