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
struct sti_hda {scalar_t__ video_dacs_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_CFG_HD_HZUVW_OFF_MASK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hda_enable_hd_dacs(struct sti_hda *hda, bool enable)
{
	if (hda->video_dacs_ctrl) {
		u32 val;

		val = readl(hda->video_dacs_ctrl);
		if (enable)
			val &= ~DAC_CFG_HD_HZUVW_OFF_MASK;
		else
			val |= DAC_CFG_HD_HZUVW_OFF_MASK;

		writel(val, hda->video_dacs_ctrl);
	}
}