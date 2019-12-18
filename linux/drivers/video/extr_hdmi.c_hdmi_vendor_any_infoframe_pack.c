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
typedef  union hdmi_vendor_any_infoframe {int dummy; } hdmi_vendor_any_infoframe ;
typedef  int ssize_t ;

/* Variables and functions */
 int hdmi_vendor_any_infoframe_check (union hdmi_vendor_any_infoframe*) ; 
 int hdmi_vendor_any_infoframe_pack_only (union hdmi_vendor_any_infoframe*,void*,size_t) ; 

__attribute__((used)) static ssize_t
hdmi_vendor_any_infoframe_pack(union hdmi_vendor_any_infoframe *frame,
			       void *buffer, size_t size)
{
	int ret;

	ret = hdmi_vendor_any_infoframe_check(frame);
	if (ret)
		return ret;

	return hdmi_vendor_any_infoframe_pack_only(frame, buffer, size);
}