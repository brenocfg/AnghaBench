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
typedef  int uint32_t ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int _PSB_IRQ_ASLE ; 
 int _PSB_VSYNC_PIPEA_FLAG ; 
 int _PSB_VSYNC_PIPEB_FLAG ; 
 int /*<<< orphan*/  mid_pipe_event_handler (struct drm_device*,int) ; 
 int /*<<< orphan*/  psb_intel_opregion_asle_intr (struct drm_device*) ; 

__attribute__((used)) static void psb_vdc_interrupt(struct drm_device *dev, uint32_t vdc_stat)
{
	if (vdc_stat & _PSB_IRQ_ASLE)
		psb_intel_opregion_asle_intr(dev);

	if (vdc_stat & _PSB_VSYNC_PIPEA_FLAG)
		mid_pipe_event_handler(dev, 0);

	if (vdc_stat & _PSB_VSYNC_PIPEB_FLAG)
		mid_pipe_event_handler(dev, 1);
}