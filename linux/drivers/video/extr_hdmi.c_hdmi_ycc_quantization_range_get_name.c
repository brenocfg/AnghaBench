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
typedef  enum hdmi_ycc_quantization_range { ____Placeholder_hdmi_ycc_quantization_range } hdmi_ycc_quantization_range ;

/* Variables and functions */
#define  HDMI_YCC_QUANTIZATION_RANGE_FULL 129 
#define  HDMI_YCC_QUANTIZATION_RANGE_LIMITED 128 

__attribute__((used)) static const char *
hdmi_ycc_quantization_range_get_name(enum hdmi_ycc_quantization_range qrange)
{
	switch (qrange) {
	case HDMI_YCC_QUANTIZATION_RANGE_LIMITED:
		return "Limited";
	case HDMI_YCC_QUANTIZATION_RANGE_FULL:
		return "Full";
	}
	return "Invalid";
}