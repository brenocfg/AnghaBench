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

/* Variables and functions */
 int /*<<< orphan*/  HPET_CFG ; 
 unsigned int HPET_CFG_ENABLE ; 
 unsigned int HPET_CFG_LEGACY ; 
 int /*<<< orphan*/  HPET_ID ; 
 unsigned int HPET_ID_NUMBER ; 
 unsigned int HPET_ID_NUMBER_SHIFT ; 
 int /*<<< orphan*/  HPET_Tn_CFG (unsigned int) ; 
 unsigned int* hpet_boot_cfg ; 
 int hpet_legacy_int_enabled ; 
 unsigned int hpet_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ hpet_virt_address ; 
 int /*<<< orphan*/  hpet_writel (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_hpet_capable () ; 

void hpet_disable(void)
{
	if (is_hpet_capable() && hpet_virt_address) {
		unsigned int cfg = hpet_readl(HPET_CFG), id, last;

		if (hpet_boot_cfg)
			cfg = *hpet_boot_cfg;
		else if (hpet_legacy_int_enabled) {
			cfg &= ~HPET_CFG_LEGACY;
			hpet_legacy_int_enabled = false;
		}
		cfg &= ~HPET_CFG_ENABLE;
		hpet_writel(cfg, HPET_CFG);

		if (!hpet_boot_cfg)
			return;

		id = hpet_readl(HPET_ID);
		last = ((id & HPET_ID_NUMBER) >> HPET_ID_NUMBER_SHIFT);

		for (id = 0; id <= last; ++id)
			hpet_writel(hpet_boot_cfg[id + 1], HPET_Tn_CFG(id));

		if (*hpet_boot_cfg & HPET_CFG_ENABLE)
			hpet_writel(*hpet_boot_cfg, HPET_CFG);
	}
}