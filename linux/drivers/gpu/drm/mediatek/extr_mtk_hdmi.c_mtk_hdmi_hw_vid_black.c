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
 int /*<<< orphan*/  GEN_RGB ; 
 int /*<<< orphan*/  NORMAL_PATH ; 
 int /*<<< orphan*/  VIDEO_CFG_4 ; 
 int /*<<< orphan*/  VIDEO_SOURCE_SEL ; 
 int /*<<< orphan*/  mtk_hdmi_mask (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_vid_black(struct mtk_hdmi *hdmi, bool black)
{
	mtk_hdmi_mask(hdmi, VIDEO_CFG_4, black ? GEN_RGB : NORMAL_PATH,
		      VIDEO_SOURCE_SEL);
}