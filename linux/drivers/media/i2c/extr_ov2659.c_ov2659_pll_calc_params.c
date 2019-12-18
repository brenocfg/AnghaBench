#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u32 ;
struct ov2659_platform_data {unsigned int link_frequency; } ;
struct TYPE_4__ {void* ctrl3; void* ctrl2; void* ctrl1; } ;
struct ov2659 {int xvclk_frequency; TYPE_1__ pll; struct i2c_client* client; struct ov2659_platform_data* pdata; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ div; void* reg; } ;
struct TYPE_5__ {scalar_t__ div; void* reg; } ;

/* Variables and functions */
 int abs (int) ; 
 TYPE_3__* ctrl1 ; 
 TYPE_2__* ctrl3 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,void*,void*,void*) ; 

__attribute__((used)) static void ov2659_pll_calc_params(struct ov2659 *ov2659)
{
	const struct ov2659_platform_data *pdata = ov2659->pdata;
	u8 ctrl1_reg = 0, ctrl2_reg = 0, ctrl3_reg = 0;
	struct i2c_client *client = ov2659->client;
	unsigned int desired = pdata->link_frequency;
	u32 prediv, postdiv, mult;
	u32 bestdelta = -1;
	u32 delta, actual;
	int i, j;

	for (i = 0; ctrl1[i].div != 0; i++) {
		postdiv = ctrl1[i].div;
		for (j = 0; ctrl3[j].div != 0; j++) {
			prediv = ctrl3[j].div;
			for (mult = 1; mult <= 63; mult++) {
				actual  = ov2659->xvclk_frequency;
				actual *= mult;
				actual /= prediv;
				actual /= postdiv;
				delta = actual - desired;
				delta = abs(delta);

				if ((delta < bestdelta) || (bestdelta == -1)) {
					bestdelta = delta;
					ctrl1_reg = ctrl1[i].reg;
					ctrl2_reg = mult;
					ctrl3_reg = ctrl3[j].reg;
				}
			}
		}
	}

	ov2659->pll.ctrl1 = ctrl1_reg;
	ov2659->pll.ctrl2 = ctrl2_reg;
	ov2659->pll.ctrl3 = ctrl3_reg;

	dev_dbg(&client->dev,
		"Actual reg config: ctrl1_reg: %02x ctrl2_reg: %02x ctrl3_reg: %02x\n",
		ctrl1_reg, ctrl2_reg, ctrl3_reg);
}