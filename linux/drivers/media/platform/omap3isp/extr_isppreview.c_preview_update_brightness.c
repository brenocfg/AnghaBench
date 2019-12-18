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
typedef  int u8 ;
struct prev_params {int brightness; int update; } ;
struct TYPE_2__ {int active; int /*<<< orphan*/  lock; struct prev_params* params; } ;
struct isp_prev_device {TYPE_1__ params; } ;

/* Variables and functions */
 int ISPPRV_BRIGHT_UNITS ; 
 int OMAP3ISP_PREV_BRIGHTNESS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
preview_update_brightness(struct isp_prev_device *prev, u8 brightness)
{
	struct prev_params *params;
	unsigned long flags;

	spin_lock_irqsave(&prev->params.lock, flags);
	params = (prev->params.active & OMAP3ISP_PREV_BRIGHTNESS)
	       ? &prev->params.params[0] : &prev->params.params[1];

	if (params->brightness != (brightness * ISPPRV_BRIGHT_UNITS)) {
		params->brightness = brightness * ISPPRV_BRIGHT_UNITS;
		params->update |= OMAP3ISP_PREV_BRIGHTNESS;
	}
	spin_unlock_irqrestore(&prev->params.lock, flags);
}