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
struct link_encoder {int dummy; } ;
struct dcn10_link_encoder {int dummy; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  DIG_BE_CNTL ; 
 int /*<<< orphan*/  DIG_MODE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 134 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 133 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 132 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 131 
#define  SIGNAL_TYPE_EDP 130 
#define  SIGNAL_TYPE_HDMI_TYPE_A 129 
#define  SIGNAL_TYPE_LVDS 128 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

void dcn10_link_encoder_setup(
	struct link_encoder *enc,
	enum signal_type signal)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	switch (signal) {
	case SIGNAL_TYPE_EDP:
	case SIGNAL_TYPE_DISPLAY_PORT:
		/* DP SST */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 0);
		break;
	case SIGNAL_TYPE_LVDS:
		/* LVDS */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 1);
		break;
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
		/* TMDS-DVI */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 2);
		break;
	case SIGNAL_TYPE_HDMI_TYPE_A:
		/* TMDS-HDMI */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 3);
		break;
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		/* DP MST */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 5);
		break;
	default:
		ASSERT_CRITICAL(false);
		/* invalid mode ! */
		break;
	}

}