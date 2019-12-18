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
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PHY_TST0 ; 
 int /*<<< orphan*/  HDMI_PHY_TST0_TSTCLR_MASK ; 
 unsigned char HDMI_PHY_TST0_TSTCLR_OFFSET ; 
 int /*<<< orphan*/  hdmi_modb (struct dw_hdmi*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hdmi_phy_test_clear(struct dw_hdmi *hdmi,
				       unsigned char bit)
{
	hdmi_modb(hdmi, bit << HDMI_PHY_TST0_TSTCLR_OFFSET,
		  HDMI_PHY_TST0_TSTCLR_MASK, HDMI_PHY_TST0);
}