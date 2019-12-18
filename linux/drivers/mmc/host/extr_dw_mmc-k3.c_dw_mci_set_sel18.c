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
struct k3_priv {int /*<<< orphan*/  reg; } ;
struct dw_mci {int /*<<< orphan*/  dev; struct k3_priv* priv; } ;

/* Variables and functions */
 unsigned int SDCARD_IO_SEL18 ; 
 int /*<<< orphan*/  SOC_SCTRL_SCPERCTRL5 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int dw_mci_set_sel18(struct dw_mci *host, bool set)
{
	int ret;
	unsigned int val;
	struct k3_priv *priv;

	priv = host->priv;

	val = set ? SDCARD_IO_SEL18 : 0;
	ret = regmap_update_bits(priv->reg, SOC_SCTRL_SCPERCTRL5,
				 SDCARD_IO_SEL18, val);
	if (ret) {
		dev_err(host->dev, "sel18 %u error\n", val);
		return ret;
	}

	return 0;
}