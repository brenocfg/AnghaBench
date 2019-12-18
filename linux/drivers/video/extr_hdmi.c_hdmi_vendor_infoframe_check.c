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
struct hdmi_vendor_infoframe {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int hdmi_vendor_infoframe_check_only (struct hdmi_vendor_infoframe*) ; 
 int /*<<< orphan*/  hdmi_vendor_infoframe_length (struct hdmi_vendor_infoframe*) ; 

int hdmi_vendor_infoframe_check(struct hdmi_vendor_infoframe *frame)
{
	frame->length = hdmi_vendor_infoframe_length(frame);

	return hdmi_vendor_infoframe_check_only(frame);
}