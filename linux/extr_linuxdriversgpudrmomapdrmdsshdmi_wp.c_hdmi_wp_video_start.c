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
struct hdmi_wp_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_WP_VIDEO_CFG ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

int hdmi_wp_video_start(struct hdmi_wp_data *wp)
{
	REG_FLD_MOD(wp->base, HDMI_WP_VIDEO_CFG, true, 31, 31);

	return 0;
}