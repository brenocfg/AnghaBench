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
struct mtk_hdmi {int dummy; } ;

/* Variables and functions */
 int CFG4_AV_UNMUTE_EN ; 
 int CFG4_AV_UNMUTE_SET ; 
 int /*<<< orphan*/  GRL_CFG4 ; 
 int /*<<< orphan*/  mtk_hdmi_mask (struct mtk_hdmi*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mtk_hdmi_hw_send_av_unmute(struct mtk_hdmi *hdmi)
{
	mtk_hdmi_mask(hdmi, GRL_CFG4, CFG4_AV_UNMUTE_EN,
		      CFG4_AV_UNMUTE_EN | CFG4_AV_UNMUTE_SET);
	usleep_range(2000, 4000);
	mtk_hdmi_mask(hdmi, GRL_CFG4, CFG4_AV_UNMUTE_SET,
		      CFG4_AV_UNMUTE_EN | CFG4_AV_UNMUTE_SET);
}