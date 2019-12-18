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
struct regmap {int dummy; } ;
struct max17042_config_data {int fullcap; int design_cap; int fullcapnom; } ;
struct max17042_chip {struct regmap* regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {struct max17042_config_data* config_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_DesignCap ; 
 int /*<<< orphan*/  MAX17042_FullCAP ; 
 int /*<<< orphan*/  MAX17042_FullCAP0 ; 
 int /*<<< orphan*/  MAX17042_FullCAPNom ; 
 int /*<<< orphan*/  MAX17042_RemCap ; 
 int /*<<< orphan*/  MAX17042_RepCap ; 
 int /*<<< orphan*/  MAX17042_RepSOC ; 
 int /*<<< orphan*/  MAX17042_VFSOC ; 
 int /*<<< orphan*/  MAX17042_dPacc ; 
 int /*<<< orphan*/  MAX17042_dQacc ; 
 int dP_ACC_200 ; 
 int dQ_ACC_DIV ; 
 int /*<<< orphan*/  max17042_write_verify_reg (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void max17042_load_new_capacity_params(struct max17042_chip *chip)
{
	u32 full_cap0, rep_cap, dq_acc, vfSoc;
	u32 rem_cap;

	struct max17042_config_data *config = chip->pdata->config_data;
	struct regmap *map = chip->regmap;

	regmap_read(map, MAX17042_FullCAP0, &full_cap0);
	regmap_read(map, MAX17042_VFSOC, &vfSoc);

	/* fg_vfSoc needs to shifted by 8 bits to get the
	 * perc in 1% accuracy, to get the right rem_cap multiply
	 * full_cap0, fg_vfSoc and devide by 100
	 */
	rem_cap = ((vfSoc >> 8) * full_cap0) / 100;
	max17042_write_verify_reg(map, MAX17042_RemCap, rem_cap);

	rep_cap = rem_cap;
	max17042_write_verify_reg(map, MAX17042_RepCap, rep_cap);

	/* Write dQ_acc to 200% of Capacity and dP_acc to 200% */
	dq_acc = config->fullcap / dQ_ACC_DIV;
	max17042_write_verify_reg(map, MAX17042_dQacc, dq_acc);
	max17042_write_verify_reg(map, MAX17042_dPacc, dP_ACC_200);

	max17042_write_verify_reg(map, MAX17042_FullCAP,
			config->fullcap);
	regmap_write(map, MAX17042_DesignCap,
			config->design_cap);
	max17042_write_verify_reg(map, MAX17042_FullCAPNom,
			config->fullcapnom);
	/* Update SOC register with new SOC */
	regmap_write(map, MAX17042_RepSOC, vfSoc);
}