#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_pmx {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct tegra_pingroup {scalar_t__ pupd_bank; scalar_t__ pupd_reg; scalar_t__ pupd_bit; scalar_t__ tri_bank; scalar_t__ tri_reg; scalar_t__ tri_bit; scalar_t__ mux_bank; scalar_t__ mux_reg; scalar_t__ einput_bit; scalar_t__ odrain_bit; scalar_t__ lock_bit; scalar_t__ ioreset_bit; scalar_t__ rcv_sel_bit; scalar_t__ drv_bank; scalar_t__ drv_reg; scalar_t__ hsm_bit; scalar_t__ schmitt_bit; scalar_t__ lpmd_bit; scalar_t__ drvdn_bit; scalar_t__ drvdn_width; scalar_t__ drvup_bit; scalar_t__ drvup_width; scalar_t__ slwf_bit; scalar_t__ slwf_width; scalar_t__ slwr_bit; scalar_t__ slwr_width; scalar_t__ drvtype_bit; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ s8 ;
typedef  scalar_t__ s32 ;
typedef  enum tegra_pinconf_param { ____Placeholder_tegra_pinconf_param } tegra_pinconf_param ;
struct TYPE_5__ {int param; char* property; } ;
struct TYPE_4__ {int /*<<< orphan*/  drvtype_in_mux; int /*<<< orphan*/  schmitt_in_mux; int /*<<< orphan*/  hsm_in_mux; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOTSUPP ; 
#define  TEGRA_PINCONF_PARAM_DRIVE_DOWN_STRENGTH 142 
#define  TEGRA_PINCONF_PARAM_DRIVE_TYPE 141 
#define  TEGRA_PINCONF_PARAM_DRIVE_UP_STRENGTH 140 
#define  TEGRA_PINCONF_PARAM_ENABLE_INPUT 139 
#define  TEGRA_PINCONF_PARAM_HIGH_SPEED_MODE 138 
#define  TEGRA_PINCONF_PARAM_IORESET 137 
#define  TEGRA_PINCONF_PARAM_LOCK 136 
#define  TEGRA_PINCONF_PARAM_LOW_POWER_MODE 135 
#define  TEGRA_PINCONF_PARAM_OPEN_DRAIN 134 
#define  TEGRA_PINCONF_PARAM_PULL 133 
#define  TEGRA_PINCONF_PARAM_RCV_SEL 132 
#define  TEGRA_PINCONF_PARAM_SCHMITT 131 
#define  TEGRA_PINCONF_PARAM_SLEW_RATE_FALLING 130 
#define  TEGRA_PINCONF_PARAM_SLEW_RATE_RISING 129 
#define  TEGRA_PINCONF_PARAM_TRISTATE 128 
 TYPE_2__* cfg_params ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int tegra_pinconf_reg(struct tegra_pmx *pmx,
			     const struct tegra_pingroup *g,
			     enum tegra_pinconf_param param,
			     bool report_err,
			     s8 *bank, s32 *reg, s8 *bit, s8 *width)
{
	switch (param) {
	case TEGRA_PINCONF_PARAM_PULL:
		*bank = g->pupd_bank;
		*reg = g->pupd_reg;
		*bit = g->pupd_bit;
		*width = 2;
		break;
	case TEGRA_PINCONF_PARAM_TRISTATE:
		*bank = g->tri_bank;
		*reg = g->tri_reg;
		*bit = g->tri_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_ENABLE_INPUT:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->einput_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_OPEN_DRAIN:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->odrain_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_LOCK:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->lock_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_IORESET:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->ioreset_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_RCV_SEL:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->rcv_sel_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_HIGH_SPEED_MODE:
		if (pmx->soc->hsm_in_mux) {
			*bank = g->mux_bank;
			*reg = g->mux_reg;
		} else {
			*bank = g->drv_bank;
			*reg = g->drv_reg;
		}
		*bit = g->hsm_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_SCHMITT:
		if (pmx->soc->schmitt_in_mux) {
			*bank = g->mux_bank;
			*reg = g->mux_reg;
		} else {
			*bank = g->drv_bank;
			*reg = g->drv_reg;
		}
		*bit = g->schmitt_bit;
		*width = 1;
		break;
	case TEGRA_PINCONF_PARAM_LOW_POWER_MODE:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->lpmd_bit;
		*width = 2;
		break;
	case TEGRA_PINCONF_PARAM_DRIVE_DOWN_STRENGTH:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->drvdn_bit;
		*width = g->drvdn_width;
		break;
	case TEGRA_PINCONF_PARAM_DRIVE_UP_STRENGTH:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->drvup_bit;
		*width = g->drvup_width;
		break;
	case TEGRA_PINCONF_PARAM_SLEW_RATE_FALLING:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->slwf_bit;
		*width = g->slwf_width;
		break;
	case TEGRA_PINCONF_PARAM_SLEW_RATE_RISING:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->slwr_bit;
		*width = g->slwr_width;
		break;
	case TEGRA_PINCONF_PARAM_DRIVE_TYPE:
		if (pmx->soc->drvtype_in_mux) {
			*bank = g->mux_bank;
			*reg = g->mux_reg;
		} else {
			*bank = g->drv_bank;
			*reg = g->drv_reg;
		}
		*bit = g->drvtype_bit;
		*width = 2;
		break;
	default:
		dev_err(pmx->dev, "Invalid config param %04x\n", param);
		return -ENOTSUPP;
	}

	if (*reg < 0 || *bit < 0)  {
		if (report_err) {
			const char *prop = "unknown";
			int i;

			for (i = 0; i < ARRAY_SIZE(cfg_params); i++) {
				if (cfg_params[i].param == param) {
					prop = cfg_params[i].property;
					break;
				}
			}

			dev_err(pmx->dev,
				"Config param %04x (%s) not supported on group %s\n",
				param, prop, g->name);
		}
		return -ENOTSUPP;
	}

	return 0;
}