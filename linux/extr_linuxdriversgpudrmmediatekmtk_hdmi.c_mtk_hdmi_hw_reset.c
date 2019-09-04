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
 int /*<<< orphan*/  ANLG_ON ; 
 int /*<<< orphan*/  CFG3_CONTROL_PACKET_DELAY ; 
 int /*<<< orphan*/  GRL_CFG3 ; 
 int /*<<< orphan*/  HDMI_RST ; 
 scalar_t__ HDMI_SYS_CFG1C ; 
 int /*<<< orphan*/  mtk_hdmi_clear_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_reset(struct mtk_hdmi *hdmi)
{
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   HDMI_RST, HDMI_RST);
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   HDMI_RST, 0);
	mtk_hdmi_clear_bits(hdmi, GRL_CFG3, CFG3_CONTROL_PACKET_DELAY);
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   ANLG_ON, ANLG_ON);
}