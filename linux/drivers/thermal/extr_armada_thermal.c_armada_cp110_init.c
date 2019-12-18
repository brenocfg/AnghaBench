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
struct armada_thermal_data {int /*<<< orphan*/  syscon_control1_off; int /*<<< orphan*/  syscon_control0_off; } ;

/* Variables and functions */
 int CONTROL0_TSEN_OSR_MAX ; 
 int CONTROL0_TSEN_OSR_SHIFT ; 
 int CONTROL1_TSEN_AVG_MASK ; 
 int /*<<< orphan*/  armada380_init (struct platform_device*,struct armada_thermal_priv*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void armada_cp110_init(struct platform_device *pdev,
			      struct armada_thermal_priv *priv)
{
	struct armada_thermal_data *data = priv->data;
	u32 reg;

	armada380_init(pdev, priv);

	/* Sample every ~2ms */
	regmap_read(priv->syscon, data->syscon_control0_off, &reg);
	reg |= CONTROL0_TSEN_OSR_MAX << CONTROL0_TSEN_OSR_SHIFT;
	regmap_write(priv->syscon, data->syscon_control0_off, reg);

	/* Average the output value over 2^1 = 2 samples */
	regmap_read(priv->syscon, data->syscon_control1_off, &reg);
	reg &= ~CONTROL1_TSEN_AVG_MASK;
	reg |= 1;
	regmap_write(priv->syscon, data->syscon_control1_off, reg);
}