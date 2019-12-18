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
typedef  int /*<<< orphan*/  u32 ;
struct brcmstb_thermal_priv {scalar_t__ tmon_base; int /*<<< orphan*/  thermal; int /*<<< orphan*/  dev; } ;
struct avs_tmon_trip {scalar_t__ reg_offs; int /*<<< orphan*/  reg_msk; int /*<<< orphan*/  reg_shift; } ;
typedef  enum avs_tmon_trip_type { ____Placeholder_avs_tmon_trip_type } avs_tmon_trip_type ;

/* Variables and functions */
 int TMON_TRIP_TYPE_LOW ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  avs_tmon_temp_to_code (int /*<<< orphan*/ ,int,int) ; 
 struct avs_tmon_trip* avs_tmon_trips ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void avs_tmon_set_trip_temp(struct brcmstb_thermal_priv *priv,
				   enum avs_tmon_trip_type type,
				   int temp)
{
	struct avs_tmon_trip *trip = &avs_tmon_trips[type];
	u32 val, orig;

	dev_dbg(priv->dev, "set temp %d to %d\n", type, temp);

	/* round toward low temp for the low interrupt */
	val = avs_tmon_temp_to_code(priv->thermal, temp,
				    type == TMON_TRIP_TYPE_LOW);

	val <<= trip->reg_shift;
	val &= trip->reg_msk;

	orig = __raw_readl(priv->tmon_base + trip->reg_offs);
	orig &= ~trip->reg_msk;
	orig |= val;
	__raw_writel(orig, priv->tmon_base + trip->reg_offs);
}