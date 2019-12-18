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
typedef  int u32 ;
struct platform_device {int dummy; } ;
struct armada_thermal_priv {int /*<<< orphan*/  syscon; struct armada_thermal_data* data; } ;
struct armada_thermal_data {int /*<<< orphan*/  syscon_status_off; int /*<<< orphan*/  syscon_control1_off; } ;

/* Variables and functions */
 int PMU_TDC0_OTF_CAL_MASK ; 
 int PMU_TDC0_REF_CAL_CNT_MASK ; 
 int PMU_TDC0_REF_CAL_CNT_OFFS ; 
 int PMU_TDC0_SW_RST_MASK ; 
 int PMU_TM_DISABLE_MASK ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void armadaxp_init(struct platform_device *pdev,
			  struct armada_thermal_priv *priv)
{
	struct armada_thermal_data *data = priv->data;
	u32 reg;

	regmap_read(priv->syscon, data->syscon_control1_off, &reg);
	reg |= PMU_TDC0_OTF_CAL_MASK;

	/* Reference calibration value */
	reg &= ~PMU_TDC0_REF_CAL_CNT_MASK;
	reg |= (0xf1 << PMU_TDC0_REF_CAL_CNT_OFFS);

	/* Reset the sensor */
	reg |= PMU_TDC0_SW_RST_MASK;

	regmap_write(priv->syscon, data->syscon_control1_off, reg);

	/* Enable the sensor */
	regmap_read(priv->syscon, data->syscon_status_off, &reg);
	reg &= ~PMU_TM_DISABLE_MASK;
	regmap_write(priv->syscon, data->syscon_status_off, reg);
}