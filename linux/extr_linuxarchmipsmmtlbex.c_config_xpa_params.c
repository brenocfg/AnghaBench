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

__attribute__((used)) static void config_xpa_params(void)
{
#ifdef CONFIG_XPA
	unsigned int pagegrain;

	if (mips_xpa_disabled) {
		pr_info("Extended Physical Addressing (XPA) disabled\n");
		return;
	}

	pagegrain = read_c0_pagegrain();
	write_c0_pagegrain(pagegrain | PG_ELPA);
	back_to_back_c0_hazard();
	pagegrain = read_c0_pagegrain();

	if (pagegrain & PG_ELPA)
		pr_info("Extended Physical Addressing (XPA) enabled\n");
	else
		panic("Extended Physical Addressing (XPA) disabled");
#endif
}