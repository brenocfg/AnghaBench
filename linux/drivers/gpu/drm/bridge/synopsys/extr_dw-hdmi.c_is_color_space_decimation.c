#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  enc_in_bus_format; int /*<<< orphan*/  enc_out_bus_format; } ;
struct dw_hdmi {TYPE_1__ hdmi_data; } ;

/* Variables and functions */
 scalar_t__ hdmi_bus_fmt_is_rgb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_bus_fmt_is_yuv422 (int /*<<< orphan*/ ) ; 
 scalar_t__ hdmi_bus_fmt_is_yuv444 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_color_space_decimation(struct dw_hdmi *hdmi)
{
	if (!hdmi_bus_fmt_is_yuv422(hdmi->hdmi_data.enc_out_bus_format))
		return 0;

	if (hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_in_bus_format) ||
	    hdmi_bus_fmt_is_yuv444(hdmi->hdmi_data.enc_in_bus_format))
		return 1;

	return 0;
}