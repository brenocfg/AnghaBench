#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct armada_thermal_priv {TYPE_1__* data; int /*<<< orphan*/  syscon; } ;
struct TYPE_2__ {int is_valid_bit; int /*<<< orphan*/  syscon_status_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool armada_is_valid(struct armada_thermal_priv *priv)
{
	u32 reg;

	if (!priv->data->is_valid_bit)
		return true;

	regmap_read(priv->syscon, priv->data->syscon_status_off, &reg);

	return reg & priv->data->is_valid_bit;
}