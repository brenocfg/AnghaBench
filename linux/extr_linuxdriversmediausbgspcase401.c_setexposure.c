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
typedef  int u8 ;
struct sd {int /*<<< orphan*/  expo_change_state; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXPO_CHANGED ; 
 int /*<<< orphan*/  HV7131_REG_TITL ; 
 int /*<<< orphan*/  HV7131_REG_TITM ; 
 int /*<<< orphan*/  HV7131_REG_TITU ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_50HZ ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_60HZ ; 
 int /*<<< orphan*/  se401_set_feature (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 val, s32 freq)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int integration = val << 6;
	u8 expose_h, expose_m, expose_l;

	/* Do this before the set_feature calls, for proper timing wrt
	   the interrupt driven pkt_scan. Note we may still race but that
	   is not a big issue, the expo change state machine is merely for
	   avoiding underexposed frames getting send out, if one sneaks
	   through so be it */
	sd->expo_change_state = EXPO_CHANGED;

	if (freq == V4L2_CID_POWER_LINE_FREQUENCY_50HZ)
		integration = integration - integration % 106667;
	if (freq == V4L2_CID_POWER_LINE_FREQUENCY_60HZ)
		integration = integration - integration % 88889;

	expose_h = (integration >> 16);
	expose_m = (integration >> 8);
	expose_l = integration;

	/* integration time low */
	se401_set_feature(gspca_dev, HV7131_REG_TITL, expose_l);
	/* integration time mid */
	se401_set_feature(gspca_dev, HV7131_REG_TITM, expose_m);
	/* integration time high */
	se401_set_feature(gspca_dev, HV7131_REG_TITU, expose_h);
}