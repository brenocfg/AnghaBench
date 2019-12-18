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
typedef  int u32 ;
struct vc4_dev {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HVS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SCALER_CHANNELS_COUNT ; 
 int /*<<< orphan*/  SCALER_DISPCTRL ; 
 int SCALER_DISPCTRL_DSPEISLUR (int) ; 
 int /*<<< orphan*/  SCALER_DISPSTAT ; 
 int SCALER_DISPSTAT_EUFLOW (int) ; 
 int SCALER_DISPSTAT_IRQMASK (int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_hvs_mask_underrun (struct drm_device*,int) ; 
 int /*<<< orphan*/  vc4_hvs_report_underrun (struct drm_device*) ; 

__attribute__((used)) static irqreturn_t vc4_hvs_irq_handler(int irq, void *data)
{
	struct drm_device *dev = data;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	irqreturn_t irqret = IRQ_NONE;
	int channel;
	u32 control;
	u32 status;

	status = HVS_READ(SCALER_DISPSTAT);
	control = HVS_READ(SCALER_DISPCTRL);

	for (channel = 0; channel < SCALER_CHANNELS_COUNT; channel++) {
		/* Interrupt masking is not always honored, so check it here. */
		if (status & SCALER_DISPSTAT_EUFLOW(channel) &&
		    control & SCALER_DISPCTRL_DSPEISLUR(channel)) {
			vc4_hvs_mask_underrun(dev, channel);
			vc4_hvs_report_underrun(dev);

			irqret = IRQ_HANDLED;
		}
	}

	/* Clear every per-channel interrupt flag. */
	HVS_WRITE(SCALER_DISPSTAT, SCALER_DISPSTAT_IRQMASK(0) |
				   SCALER_DISPSTAT_IRQMASK(1) |
				   SCALER_DISPSTAT_IRQMASK(2));

	return irqret;
}