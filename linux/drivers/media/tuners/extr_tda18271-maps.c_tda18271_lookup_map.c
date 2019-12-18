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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct tda18271_priv {TYPE_1__* maps; } ;
struct tda18271_map {int rfmax; int /*<<< orphan*/  val; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;
typedef  enum tda18271_map_type { ____Placeholder_tda18271_map_type } tda18271_map_type ;
struct TYPE_2__ {struct tda18271_map* rf_cal_dc_over_dt; struct tda18271_map* ir_measure; struct tda18271_map* rf_cal; struct tda18271_map* gain_taper; struct tda18271_map* rf_band; struct tda18271_map* rf_cal_kmco; struct tda18271_map* bp_filter; } ;

/* Variables and functions */
#define  BP_FILTER 134 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ERANGE ; 
#define  GAIN_TAPER 133 
#define  IR_MEASURE 132 
#define  RF_BAND 131 
#define  RF_CAL 130 
#define  RF_CAL_DC_OVER_DT 129 
#define  RF_CAL_KMCO 128 
 int /*<<< orphan*/  tda_map (char*,...) ; 
 int /*<<< orphan*/  tda_warn (char*,char*) ; 

int tda18271_lookup_map(struct dvb_frontend *fe,
			enum tda18271_map_type map_type,
			u32 *freq, u8 *val)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	struct tda18271_map *map = NULL;
	unsigned int i = 0;
	char *map_name;
	int ret = 0;

	BUG_ON(!priv->maps);

	switch (map_type) {
	case BP_FILTER:
		map = priv->maps->bp_filter;
		map_name = "bp_filter";
		break;
	case RF_CAL_KMCO:
		map = priv->maps->rf_cal_kmco;
		map_name = "km";
		break;
	case RF_BAND:
		map = priv->maps->rf_band;
		map_name = "rf_band";
		break;
	case GAIN_TAPER:
		map = priv->maps->gain_taper;
		map_name = "gain_taper";
		break;
	case RF_CAL:
		map = priv->maps->rf_cal;
		map_name = "rf_cal";
		break;
	case IR_MEASURE:
		map = priv->maps->ir_measure;
		map_name = "ir_measure";
		break;
	case RF_CAL_DC_OVER_DT:
		map = priv->maps->rf_cal_dc_over_dt;
		map_name = "rf_cal_dc_over_dt";
		break;
	default:
		/* we should never get here */
		map_name = "undefined";
		break;
	}

	if (!map) {
		tda_warn("%s map is not set!\n", map_name);
		ret = -EINVAL;
		goto fail;
	}

	while ((map[i].rfmax * 1000) < *freq) {
		if (map[i + 1].rfmax == 0) {
			tda_map("%s: frequency (%d) out of range\n",
				map_name, *freq);
			ret = -ERANGE;
			break;
		}
		i++;
	}
	*val = map[i].val;

	tda_map("(%d) %s: 0x%02x\n", i, map_name, *val);
fail:
	return ret;
}