#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned long hdisplay; unsigned long vdisplay; int /*<<< orphan*/  pll2_config_value; int /*<<< orphan*/  pll1_config_value; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CRT_PLL1_HS_25MHZ ; 
 int /*<<< orphan*/  CRT_PLL2_HS_25MHZ ; 
 TYPE_1__* hibmc_pll_table ; 

__attribute__((used)) static void get_pll_config(unsigned long x, unsigned long y,
			   u32 *pll1, u32 *pll2)
{
	int i;
	int count = ARRAY_SIZE(hibmc_pll_table);

	for (i = 0; i < count; i++) {
		if (hibmc_pll_table[i].hdisplay == x &&
		    hibmc_pll_table[i].vdisplay == y) {
			*pll1 = hibmc_pll_table[i].pll1_config_value;
			*pll2 = hibmc_pll_table[i].pll2_config_value;
			return;
		}
	}

	/* if found none, we use default value */
	*pll1 = CRT_PLL1_HS_25MHZ;
	*pll2 = CRT_PLL2_HS_25MHZ;
}