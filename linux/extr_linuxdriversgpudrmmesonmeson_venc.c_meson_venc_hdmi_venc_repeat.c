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

bool meson_venc_hdmi_venc_repeat(int vic)
{
	/* Repeat VENC pixels for 480/576i/p, 720p50/60 and 1080p50/60 */
	if (vic == 6 || vic == 7 || /* 480i */
	    vic == 21 || vic == 22 || /* 576i */
	    vic == 17 || vic == 18 || /* 576p */
	    vic == 2 || vic == 3 || /* 480p */
	    vic == 4 || /* 720p60 */
	    vic == 19 || /* 720p50 */
	    vic == 5 || /* 1080i60 */
	    vic == 20)	/* 1080i50 */
		return true;

	return false;
}