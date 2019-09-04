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

/* Variables and functions */
 int /*<<< orphan*/  VPIF_CH2_CLIP_ACTIVE_EN ; 
 int /*<<< orphan*/  VPIF_CH2_CLIP_ANC_EN ; 
 int /*<<< orphan*/  VPIF_CH2_CTRL ; 
 int /*<<< orphan*/  vpif_clr_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void channel2_clipping_enable(int enable)
{
	if (enable) {
		vpif_set_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ANC_EN);
		vpif_set_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ACTIVE_EN);
	} else {
		vpif_clr_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ANC_EN);
		vpif_clr_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ACTIVE_EN);
	}
}