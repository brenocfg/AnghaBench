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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVReadRAMDAC (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_PRAMDAC_CU_START_POS ; 

__attribute__((used)) static inline void
nv_fix_nv40_hw_cursor(struct drm_device *dev, int head)
{
	/* on some nv40 (such as the "true" (in the NV_PFB_BOOT_0 sense) nv40,
	 * the gf6800gt) a hardware bug requires a write to PRAMDAC_CURSOR_POS
	 * for changes to the CRTC CURCTL regs to take effect, whether changing
	 * the pixmap location, or just showing/hiding the cursor
	 */
	uint32_t curpos = NVReadRAMDAC(dev, head, NV_PRAMDAC_CU_START_POS);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_CU_START_POS, curpos);
}