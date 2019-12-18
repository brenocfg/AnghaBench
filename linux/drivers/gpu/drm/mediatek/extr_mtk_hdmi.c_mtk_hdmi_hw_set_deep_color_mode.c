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
struct mtk_hdmi {scalar_t__ sys_offset; int /*<<< orphan*/  sys_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_8BIT_MODE ; 
 int DEEP_COLOR_EN ; 
 int DEEP_COLOR_MODE_MASK ; 
 scalar_t__ HDMI_SYS_CFG20 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_set_deep_color_mode(struct mtk_hdmi *hdmi)
{
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG20,
			   DEEP_COLOR_MODE_MASK | DEEP_COLOR_EN,
			   COLOR_8BIT_MODE);
}