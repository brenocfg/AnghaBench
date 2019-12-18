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
struct hdmi_avi_infoframe {int dummy; } ;

/* Variables and functions */
 int hdmi_avi_infoframe_check_only (struct hdmi_avi_infoframe*) ; 

int hdmi_avi_infoframe_check(struct hdmi_avi_infoframe *frame)
{
	return hdmi_avi_infoframe_check_only(frame);
}