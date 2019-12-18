#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tps80031_regulator_platform_data {int dummy; } ;
struct tps80031_regulator {int config_flags; int /*<<< orphan*/  dev; TYPE_2__* rinfo; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  trans_reg; TYPE_1__ desc; } ;

/* Variables and functions */
 int MISC2_LDO3_SEL_VIB_MASK ; 
 unsigned int MISC2_LDO3_SEL_VIB_VAL ; 
 int MISC2_LDOUSB_IN_MASK ; 
 unsigned int MISC2_LDOUSB_IN_PMID ; 
 unsigned int MISC2_LDOUSB_IN_VSYS ; 
 int TPS80031_LDO3_OUTPUT_VIB ; 
 int /*<<< orphan*/  TPS80031_MISC2 ; 
#define  TPS80031_REGULATOR_LDO3 130 
#define  TPS80031_REGULATOR_LDOUSB 129 
#define  TPS80031_REGULATOR_VBUS 128 
 int /*<<< orphan*/  TPS80031_SLAVE_ID1 ; 
 int TPS80031_TRANS_ACTIVE_MASK ; 
 unsigned int TPS80031_TRANS_ACTIVE_ON ; 
 int TPS80031_TRANS_OFF_MASK ; 
 unsigned int TPS80031_TRANS_OFF_OFF ; 
 int TPS80031_TRANS_SLEEP_MASK ; 
 unsigned int TPS80031_TRANS_SLEEP_OFF ; 
 int TPS80031_USBLDO_INPUT_PMID ; 
 int TPS80031_USBLDO_INPUT_VSYS ; 
 int TPS80031_VBUS_SW_ONLY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int tps80031_update (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  tps80031_vbus_sw_ops ; 

__attribute__((used)) static int tps80031_regulator_config(struct device *parent,
		struct tps80031_regulator *ri,
		struct tps80031_regulator_platform_data *tps80031_pdata)
{
	int ret = 0;

	switch (ri->rinfo->desc.id) {
	case TPS80031_REGULATOR_LDOUSB:
		if (ri->config_flags & (TPS80031_USBLDO_INPUT_VSYS |
			TPS80031_USBLDO_INPUT_PMID)) {
			unsigned val = 0;
			if (ri->config_flags & TPS80031_USBLDO_INPUT_VSYS)
				val = MISC2_LDOUSB_IN_VSYS;
			else
				val = MISC2_LDOUSB_IN_PMID;

			ret = tps80031_update(parent, TPS80031_SLAVE_ID1,
				TPS80031_MISC2, val,
				MISC2_LDOUSB_IN_MASK);
			if (ret < 0) {
				dev_err(ri->dev,
					"LDOUSB config failed, e= %d\n", ret);
				return ret;
			}
		}
		break;

	case TPS80031_REGULATOR_LDO3:
		if (ri->config_flags & TPS80031_LDO3_OUTPUT_VIB) {
			ret = tps80031_update(parent, TPS80031_SLAVE_ID1,
				TPS80031_MISC2, MISC2_LDO3_SEL_VIB_VAL,
				MISC2_LDO3_SEL_VIB_MASK);
			if (ret < 0) {
				dev_err(ri->dev,
					"LDO3 config failed, e = %d\n", ret);
				return ret;
			}
		}
		break;

	case TPS80031_REGULATOR_VBUS:
		/* Provide SW control Ops if VBUS is SW control */
		if (!(ri->config_flags & TPS80031_VBUS_SW_ONLY))
			ri->rinfo->desc.ops = &tps80031_vbus_sw_ops;
		break;
	default:
		break;
	}

	/* Configure Active state to ON, SLEEP to OFF and OFF_state to OFF */
	ret = tps80031_update(parent, TPS80031_SLAVE_ID1, ri->rinfo->trans_reg,
		TPS80031_TRANS_ACTIVE_ON | TPS80031_TRANS_SLEEP_OFF |
		TPS80031_TRANS_OFF_OFF, TPS80031_TRANS_ACTIVE_MASK |
		TPS80031_TRANS_SLEEP_MASK | TPS80031_TRANS_OFF_MASK);
	if (ret < 0) {
		dev_err(ri->dev, "trans reg update failed, e %d\n", ret);
		return ret;
	}

	return ret;
}