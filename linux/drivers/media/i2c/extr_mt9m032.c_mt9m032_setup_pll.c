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
typedef  int u16 ;
struct mt9m032_platform_data {int /*<<< orphan*/  pix_clock; int /*<<< orphan*/  ext_clock; } ;
struct mt9m032 {int /*<<< orphan*/  pix_clock; struct mt9m032_platform_data* pdata; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct aptina_pll_limits {int ext_clock_min; int ext_clock_max; int int_clock_min; int int_clock_max; int out_clock_min; int out_clock_max; int pix_clock_max; int n_min; int n_max; int m_min; int m_max; int p1_min; int p1_max; } ;
struct aptina_pll {int m; int n; int p1; int /*<<< orphan*/  pix_clock; int /*<<< orphan*/  ext_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M032_FORMATTER1 ; 
 int MT9M032_FORMATTER1_PARALLEL ; 
 int MT9M032_FORMATTER1_PLL_P1_6 ; 
 int /*<<< orphan*/  MT9M032_PLL_CONFIG1 ; 
 int MT9M032_PLL_CONFIG1_MUL_SHIFT ; 
 int MT9M032_PLL_CONFIG1_PREDIV_MASK ; 
 int /*<<< orphan*/  MT9M032_READ_MODE1 ; 
 int MT9M032_READ_MODE1_STROBE_END_SHUTTER ; 
 int MT9M032_READ_MODE1_STROBE_START_EXP ; 
 int /*<<< orphan*/  MT9P031_PLL_CONTROL ; 
 int MT9P031_PLL_CONTROL_PWRON ; 
 int MT9P031_PLL_CONTROL_USEPLL ; 
 int aptina_pll_calculate (int /*<<< orphan*/ *,struct aptina_pll_limits const*,struct aptina_pll*) ; 
 int mt9m032_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m032_setup_pll(struct mt9m032 *sensor)
{
	static const struct aptina_pll_limits limits = {
		.ext_clock_min = 8000000,
		.ext_clock_max = 16500000,
		.int_clock_min = 2000000,
		.int_clock_max = 24000000,
		.out_clock_min = 322000000,
		.out_clock_max = 693000000,
		.pix_clock_max = 99000000,
		.n_min = 1,
		.n_max = 64,
		.m_min = 16,
		.m_max = 255,
		.p1_min = 6,
		.p1_max = 7,
	};

	struct i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	struct mt9m032_platform_data *pdata = sensor->pdata;
	struct aptina_pll pll;
	u16 reg_val;
	int ret;

	pll.ext_clock = pdata->ext_clock;
	pll.pix_clock = pdata->pix_clock;

	ret = aptina_pll_calculate(&client->dev, &limits, &pll);
	if (ret < 0)
		return ret;

	sensor->pix_clock = pdata->pix_clock;

	ret = mt9m032_write(client, MT9M032_PLL_CONFIG1,
			    (pll.m << MT9M032_PLL_CONFIG1_MUL_SHIFT) |
			    ((pll.n - 1) & MT9M032_PLL_CONFIG1_PREDIV_MASK));
	if (!ret)
		ret = mt9m032_write(client, MT9P031_PLL_CONTROL,
				    MT9P031_PLL_CONTROL_PWRON |
				    MT9P031_PLL_CONTROL_USEPLL);
	if (!ret)		/* more reserved, Continuous, Master Mode */
		ret = mt9m032_write(client, MT9M032_READ_MODE1, 0x8000 |
				    MT9M032_READ_MODE1_STROBE_START_EXP |
				    MT9M032_READ_MODE1_STROBE_END_SHUTTER);
	if (!ret) {
		reg_val = (pll.p1 == 6 ? MT9M032_FORMATTER1_PLL_P1_6 : 0)
			| MT9M032_FORMATTER1_PARALLEL | 0x001e; /* 14-bit */
		ret = mt9m032_write(client, MT9M032_FORMATTER1, reg_val);
	}

	return ret;
}