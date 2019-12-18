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
typedef  int uint32_t ;
struct link_encoder {int dummy; } ;
struct dcn10_link_encoder {int dummy; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  DIG_BE_CNTL ; 
 int /*<<< orphan*/  DIG_MODE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int SIGNAL_TYPE_DISPLAY_PORT ; 
 int SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 int SIGNAL_TYPE_DVI_SINGLE_LINK ; 
 int SIGNAL_TYPE_HDMI_TYPE_A ; 
 int SIGNAL_TYPE_NONE ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

enum signal_type dcn10_get_dig_mode(
	struct link_encoder *enc)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	uint32_t value;
	REG_GET(DIG_BE_CNTL, DIG_MODE, &value);
	switch (value) {
	case 1:
		return SIGNAL_TYPE_DISPLAY_PORT;
	case 2:
		return SIGNAL_TYPE_DVI_SINGLE_LINK;
	case 3:
		return SIGNAL_TYPE_HDMI_TYPE_A;
	case 5:
		return SIGNAL_TYPE_DISPLAY_PORT_MST;
	default:
		return SIGNAL_TYPE_NONE;
	}
	return SIGNAL_TYPE_NONE;
}