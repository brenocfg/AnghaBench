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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct isc_subdev_entity {int pfe_cfg0; } ;
struct isc_format {int /*<<< orphan*/  fourcc; } ;
struct TYPE_4__ {int /*<<< orphan*/  hist_stat; } ;
struct isc_device {TYPE_2__ ctrls; struct isc_subdev_entity* current_subdev; TYPE_1__* raw_fmt; struct isc_format* current_fmt; struct regmap* regmap; } ;
struct fmt_config {int pfe_cfg0_bps; int bits_pipeline; int rlp_cfg_mode; int dcfg_imode; } ;
struct TYPE_3__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIST_INIT ; 
 int /*<<< orphan*/  ISC_DCFG ; 
 int ISC_DCFG_CMBSIZE_BEATS8 ; 
 int ISC_DCFG_YMBSIZE_BEATS8 ; 
 int /*<<< orphan*/  ISC_PFE_CFG0 ; 
 int ISC_PFE_CFG0_BPS_MASK ; 
 int ISC_PFE_CFG0_HPOL_LOW ; 
 int ISC_PFE_CFG0_MODE_MASK ; 
 int ISC_PFE_CFG0_MODE_PROGRESSIVE ; 
 int ISC_PFE_CFG0_PPOL_LOW ; 
 int ISC_PFE_CFG0_VPOL_LOW ; 
 int /*<<< orphan*/  ISC_RLP_CFG ; 
 int ISC_RLP_CFG_MODE_MASK ; 
 struct fmt_config* get_fmt_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_get_param (struct isc_format const*,int*,int*) ; 
 int /*<<< orphan*/  isc_set_histogram (struct isc_device*) ; 
 int /*<<< orphan*/  isc_set_pipeline (struct isc_device*,int) ; 
 int isc_update_profile (struct isc_device*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sensor_is_preferred (struct isc_format const*) ; 

__attribute__((used)) static int isc_configure(struct isc_device *isc)
{
	struct regmap *regmap = isc->regmap;
	const struct isc_format *current_fmt = isc->current_fmt;
	struct fmt_config *curfmt_config = get_fmt_config(current_fmt->fourcc);
	struct fmt_config *rawfmt_config = get_fmt_config(isc->raw_fmt->fourcc);
	struct isc_subdev_entity *subdev = isc->current_subdev;
	u32 pfe_cfg0, rlp_mode, dcfg, mask, pipeline;

	if (sensor_is_preferred(current_fmt)) {
		pfe_cfg0 = curfmt_config->pfe_cfg0_bps;
		pipeline = 0x0;
		isc_get_param(current_fmt, &rlp_mode, &dcfg);
		isc->ctrls.hist_stat = HIST_INIT;
	} else {
		pfe_cfg0 = rawfmt_config->pfe_cfg0_bps;
		pipeline = curfmt_config->bits_pipeline;
		rlp_mode = curfmt_config->rlp_cfg_mode;
		dcfg = curfmt_config->dcfg_imode |
		       ISC_DCFG_YMBSIZE_BEATS8 | ISC_DCFG_CMBSIZE_BEATS8;
	}

	pfe_cfg0  |= subdev->pfe_cfg0 | ISC_PFE_CFG0_MODE_PROGRESSIVE;
	mask = ISC_PFE_CFG0_BPS_MASK | ISC_PFE_CFG0_HPOL_LOW |
	       ISC_PFE_CFG0_VPOL_LOW | ISC_PFE_CFG0_PPOL_LOW |
	       ISC_PFE_CFG0_MODE_MASK;

	regmap_update_bits(regmap, ISC_PFE_CFG0, mask, pfe_cfg0);

	regmap_update_bits(regmap, ISC_RLP_CFG, ISC_RLP_CFG_MODE_MASK,
			   rlp_mode);

	regmap_write(regmap, ISC_DCFG, dcfg);

	/* Set the pipeline */
	isc_set_pipeline(isc, pipeline);

	if (pipeline)
		isc_set_histogram(isc);

	/* Update profile */
	return isc_update_profile(isc);
}