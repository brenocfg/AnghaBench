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
struct palmas_pctrl_chip_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_PRIMARY_SECONDARY_PAD3 ; 
 int PALMAS_PRIMARY_SECONDARY_PAD3_DVFS2 ; 
 int /*<<< orphan*/  PALMAS_PU_PD_OD_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int palmas_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int palmas_pinctrl_set_dvfs2(struct palmas_pctrl_chip_info *pci,
		bool enable)
{
	int ret;
	int val;

	val = enable ? PALMAS_PRIMARY_SECONDARY_PAD3_DVFS2 : 0;
	ret = palmas_update_bits(pci->palmas, PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD3,
			PALMAS_PRIMARY_SECONDARY_PAD3_DVFS2, val);
	if (ret < 0)
		dev_err(pci->dev, "SECONDARY_PAD3 update failed %d\n", ret);
	return ret;
}