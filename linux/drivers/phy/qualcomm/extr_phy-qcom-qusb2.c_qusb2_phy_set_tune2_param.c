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
typedef  int u8 ;
struct qusb2_phy_cfg {int /*<<< orphan*/ * regs; scalar_t__ update_tune1_with_efuse; } ;
struct qusb2_phy {int /*<<< orphan*/  base; int /*<<< orphan*/  cell; struct qusb2_phy_cfg* cfg; TYPE_1__* phy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSTX_TRIM_MASK ; 
 int HSTX_TRIM_SHIFT ; 
 scalar_t__ IS_ERR (int*) ; 
 size_t QUSB2PHY_PORT_TUNE1 ; 
 size_t QUSB2PHY_PORT_TUNE2 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int* nvmem_cell_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qusb2_write_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qusb2_phy_set_tune2_param(struct qusb2_phy *qphy)
{
	struct device *dev = &qphy->phy->dev;
	const struct qusb2_phy_cfg *cfg = qphy->cfg;
	u8 *val;

	/* efuse register is optional */
	if (!qphy->cell)
		return;

	/*
	 * Read efuse register having TUNE2/1 parameter's high nibble.
	 * If efuse register shows value as 0x0 (indicating value is not
	 * fused), or if we fail to find a valid efuse register setting,
	 * then use default value for high nibble that we have already
	 * set while configuring the phy.
	 */
	val = nvmem_cell_read(qphy->cell, NULL);
	if (IS_ERR(val) || !val[0]) {
		dev_dbg(dev, "failed to read a valid hs-tx trim value\n");
		return;
	}

	/* Fused TUNE1/2 value is the higher nibble only */
	if (cfg->update_tune1_with_efuse)
		qusb2_write_mask(qphy->base, cfg->regs[QUSB2PHY_PORT_TUNE1],
				 val[0] << HSTX_TRIM_SHIFT,
				 HSTX_TRIM_MASK);
	else
		qusb2_write_mask(qphy->base, cfg->regs[QUSB2PHY_PORT_TUNE2],
				 val[0] << HSTX_TRIM_SHIFT,
				 HSTX_TRIM_MASK);
}