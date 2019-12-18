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
struct isc_ctrls {int* offset; int* gain; } ;
struct isc_device {int /*<<< orphan*/  regmap; struct isc_ctrls ctrls; } ;

/* Variables and functions */
 size_t ISC_HIS_CFG_MODE_B ; 
 size_t ISC_HIS_CFG_MODE_GB ; 
 size_t ISC_HIS_CFG_MODE_GR ; 
 size_t ISC_HIS_CFG_MODE_R ; 
 int /*<<< orphan*/  ISC_WB_G_BGB ; 
 int /*<<< orphan*/  ISC_WB_G_RGR ; 
 int /*<<< orphan*/  ISC_WB_O_BGB ; 
 int /*<<< orphan*/  ISC_WB_O_RGR ; 
 int ISC_WB_O_ZERO_VAL ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void isc_update_awb_ctrls(struct isc_device *isc)
{
	struct isc_ctrls *ctrls = &isc->ctrls;

	regmap_write(isc->regmap, ISC_WB_O_RGR,
		     (ISC_WB_O_ZERO_VAL - (ctrls->offset[ISC_HIS_CFG_MODE_R])) |
		     ((ISC_WB_O_ZERO_VAL - ctrls->offset[ISC_HIS_CFG_MODE_GR]) << 16));
	regmap_write(isc->regmap, ISC_WB_O_BGB,
		     (ISC_WB_O_ZERO_VAL - (ctrls->offset[ISC_HIS_CFG_MODE_B])) |
		     ((ISC_WB_O_ZERO_VAL - ctrls->offset[ISC_HIS_CFG_MODE_GB]) << 16));
	regmap_write(isc->regmap, ISC_WB_G_RGR,
		     ctrls->gain[ISC_HIS_CFG_MODE_R] |
		     (ctrls->gain[ISC_HIS_CFG_MODE_GR] << 16));
	regmap_write(isc->regmap, ISC_WB_G_BGB,
		     ctrls->gain[ISC_HIS_CFG_MODE_B] |
		     (ctrls->gain[ISC_HIS_CFG_MODE_GB] << 16));
}