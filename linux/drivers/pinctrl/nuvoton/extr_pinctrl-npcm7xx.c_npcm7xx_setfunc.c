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
struct regmap {int dummy; } ;
struct npcm7xx_pincfg {int fn0; int fn1; int fn2; int /*<<< orphan*/  bit2; scalar_t__ reg2; int /*<<< orphan*/  bit1; scalar_t__ reg1; int /*<<< orphan*/  bit0; scalar_t__ reg0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int fn_gpio ; 
 struct npcm7xx_pincfg* pincfg ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npcm7xx_setfunc(struct regmap *gcr_regmap, const unsigned int *pin,
			    int pin_number, int mode)
{
	const struct npcm7xx_pincfg *cfg;
	int i;

	for (i = 0 ; i < pin_number ; i++) {
		cfg = &pincfg[pin[i]];
		if (mode == fn_gpio || cfg->fn0 == mode || cfg->fn1 == mode || cfg->fn2 == mode) {
			if (cfg->reg0)
				regmap_update_bits(gcr_regmap, cfg->reg0,
						   BIT(cfg->bit0),
						   !!(cfg->fn0 == mode) ?
						   BIT(cfg->bit0) : 0);
			if (cfg->reg1)
				regmap_update_bits(gcr_regmap, cfg->reg1,
						   BIT(cfg->bit1),
						   !!(cfg->fn1 == mode) ?
						   BIT(cfg->bit1) : 0);
			if (cfg->reg2)
				regmap_update_bits(gcr_regmap, cfg->reg2,
						   BIT(cfg->bit2),
						   !!(cfg->fn2 == mode) ?
						   BIT(cfg->bit2) : 0);
		}
	}
}