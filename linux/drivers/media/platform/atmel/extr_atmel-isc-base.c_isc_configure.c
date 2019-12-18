#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regmap {int dummy; } ;
struct isc_subdev_entity {int pfe_cfg0; } ;
struct TYPE_6__ {int rlp_cfg_mode; int bits_pipeline; int dcfg_imode; TYPE_2__* sd_format; } ;
struct TYPE_4__ {scalar_t__ awb; } ;
struct isc_device {TYPE_3__ config; TYPE_1__ ctrls; struct isc_subdev_entity* current_subdev; struct regmap* regmap; } ;
struct TYPE_5__ {int pfe_cfg0_bps; int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_DCFG ; 
 int ISC_DCFG_CMBSIZE_BEATS8 ; 
 int ISC_DCFG_YMBSIZE_BEATS8 ; 
 scalar_t__ ISC_IS_FORMAT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_PFE_CFG0 ; 
 int ISC_PFE_CFG0_BPS_MASK ; 
 int ISC_PFE_CFG0_CCIR656 ; 
 int ISC_PFE_CFG0_CCIR_CRC ; 
 int ISC_PFE_CFG0_HPOL_LOW ; 
 int ISC_PFE_CFG0_MODE_MASK ; 
 int ISC_PFE_CFG0_MODE_PROGRESSIVE ; 
 int ISC_PFE_CFG0_PPOL_LOW ; 
 int ISC_PFE_CFG0_VPOL_LOW ; 
 int /*<<< orphan*/  ISC_RLP_CFG ; 
 int ISC_RLP_CFG_MODE_MASK ; 
 int /*<<< orphan*/  isc_set_histogram (struct isc_device*,int) ; 
 int /*<<< orphan*/  isc_set_pipeline (struct isc_device*,int) ; 
 int isc_update_profile (struct isc_device*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isc_configure(struct isc_device *isc)
{
	struct regmap *regmap = isc->regmap;
	u32 pfe_cfg0, rlp_mode, dcfg, mask, pipeline;
	struct isc_subdev_entity *subdev = isc->current_subdev;

	pfe_cfg0 = isc->config.sd_format->pfe_cfg0_bps;
	rlp_mode = isc->config.rlp_cfg_mode;
	pipeline = isc->config.bits_pipeline;

	dcfg = isc->config.dcfg_imode |
		       ISC_DCFG_YMBSIZE_BEATS8 | ISC_DCFG_CMBSIZE_BEATS8;

	pfe_cfg0  |= subdev->pfe_cfg0 | ISC_PFE_CFG0_MODE_PROGRESSIVE;
	mask = ISC_PFE_CFG0_BPS_MASK | ISC_PFE_CFG0_HPOL_LOW |
	       ISC_PFE_CFG0_VPOL_LOW | ISC_PFE_CFG0_PPOL_LOW |
	       ISC_PFE_CFG0_MODE_MASK | ISC_PFE_CFG0_CCIR_CRC |
		   ISC_PFE_CFG0_CCIR656;

	regmap_update_bits(regmap, ISC_PFE_CFG0, mask, pfe_cfg0);

	regmap_update_bits(regmap, ISC_RLP_CFG, ISC_RLP_CFG_MODE_MASK,
			   rlp_mode);

	regmap_write(regmap, ISC_DCFG, dcfg);

	/* Set the pipeline */
	isc_set_pipeline(isc, pipeline);

	/*
	 * The current implemented histogram is available for RAW R, B, GB, GR
	 * channels. We need to check if sensor is outputting RAW BAYER
	 */
	if (isc->ctrls.awb &&
	    ISC_IS_FORMAT_RAW(isc->config.sd_format->mbus_code))
		isc_set_histogram(isc, true);
	else
		isc_set_histogram(isc, false);

	/* Update profile */
	return isc_update_profile(isc);
}