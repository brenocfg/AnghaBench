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
struct regmap {int dummy; } ;
struct max17042_config_data {int /*<<< orphan*/  qrtbl30; int /*<<< orphan*/  qrtbl20; int /*<<< orphan*/  qrtbl10; int /*<<< orphan*/  qrtbl00; int /*<<< orphan*/  kempty0; int /*<<< orphan*/  empty_tempco; int /*<<< orphan*/  ichgt_term; int /*<<< orphan*/  tcompc0; int /*<<< orphan*/  rcomp0; } ;
struct max17042_chip {scalar_t__ chip_type; struct regmap* regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {struct max17042_config_data* config_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_EmptyTempCo ; 
 int /*<<< orphan*/  MAX17042_ICHGTerm ; 
 int /*<<< orphan*/  MAX17042_K_empty0 ; 
 int /*<<< orphan*/  MAX17042_RCOMP0 ; 
 int /*<<< orphan*/  MAX17042_TempCo ; 
 int /*<<< orphan*/  MAX17047_QRTbl00 ; 
 int /*<<< orphan*/  MAX17047_QRTbl10 ; 
 int /*<<< orphan*/  MAX17047_QRTbl20 ; 
 int /*<<< orphan*/  MAX17047_QRTbl30 ; 
 scalar_t__ MAXIM_DEVICE_TYPE_MAX17042 ; 
 int /*<<< orphan*/  max17042_write_verify_reg (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void  max17042_write_custom_regs(struct max17042_chip *chip)
{
	struct max17042_config_data *config = chip->pdata->config_data;
	struct regmap *map = chip->regmap;

	max17042_write_verify_reg(map, MAX17042_RCOMP0, config->rcomp0);
	max17042_write_verify_reg(map, MAX17042_TempCo,	config->tcompc0);
	max17042_write_verify_reg(map, MAX17042_ICHGTerm, config->ichgt_term);
	if (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042) {
		regmap_write(map, MAX17042_EmptyTempCo,	config->empty_tempco);
		max17042_write_verify_reg(map, MAX17042_K_empty0,
					config->kempty0);
	} else {
		max17042_write_verify_reg(map, MAX17047_QRTbl00,
						config->qrtbl00);
		max17042_write_verify_reg(map, MAX17047_QRTbl10,
						config->qrtbl10);
		max17042_write_verify_reg(map, MAX17047_QRTbl20,
						config->qrtbl20);
		max17042_write_verify_reg(map, MAX17047_QRTbl30,
						config->qrtbl30);
	}
}