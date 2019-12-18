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
typedef  int /*<<< orphan*/  u32 ;
struct vc4_dev {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_DISPCTRL ; 
 int /*<<< orphan*/  SCALER_DISPCTRL_DSPEISLUR (int) ; 
 int /*<<< orphan*/  SCALER_DISPSTAT ; 
 int /*<<< orphan*/  SCALER_DISPSTAT_EUFLOW (int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

void vc4_hvs_unmask_underrun(struct drm_device *dev, int channel)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	u32 dispctrl = HVS_READ(SCALER_DISPCTRL);

	dispctrl |= SCALER_DISPCTRL_DSPEISLUR(channel);

	HVS_WRITE(SCALER_DISPSTAT,
		  SCALER_DISPSTAT_EUFLOW(channel));
	HVS_WRITE(SCALER_DISPCTRL, dispctrl);
}