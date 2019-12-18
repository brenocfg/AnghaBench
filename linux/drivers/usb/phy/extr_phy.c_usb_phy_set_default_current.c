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
struct TYPE_2__ {int /*<<< orphan*/  aca_max; int /*<<< orphan*/  aca_min; int /*<<< orphan*/  cdp_max; int /*<<< orphan*/  cdp_min; int /*<<< orphan*/  dcp_max; int /*<<< orphan*/  dcp_min; int /*<<< orphan*/  sdp_max; int /*<<< orphan*/  sdp_min; } ;
struct usb_phy {TYPE_1__ chg_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ACA_CUR_MAX ; 
 int /*<<< orphan*/  DEFAULT_ACA_CUR_MIN ; 
 int /*<<< orphan*/  DEFAULT_CDP_CUR_MAX ; 
 int /*<<< orphan*/  DEFAULT_CDP_CUR_MIN ; 
 int /*<<< orphan*/  DEFAULT_DCP_CUR_MAX ; 
 int /*<<< orphan*/  DEFAULT_DCP_CUR_MIN ; 
 int /*<<< orphan*/  DEFAULT_SDP_CUR_MAX ; 
 int /*<<< orphan*/  DEFAULT_SDP_CUR_MIN ; 

__attribute__((used)) static void usb_phy_set_default_current(struct usb_phy *usb_phy)
{
	usb_phy->chg_cur.sdp_min = DEFAULT_SDP_CUR_MIN;
	usb_phy->chg_cur.sdp_max = DEFAULT_SDP_CUR_MAX;
	usb_phy->chg_cur.dcp_min = DEFAULT_DCP_CUR_MIN;
	usb_phy->chg_cur.dcp_max = DEFAULT_DCP_CUR_MAX;
	usb_phy->chg_cur.cdp_min = DEFAULT_CDP_CUR_MIN;
	usb_phy->chg_cur.cdp_max = DEFAULT_CDP_CUR_MAX;
	usb_phy->chg_cur.aca_min = DEFAULT_ACA_CUR_MIN;
	usb_phy->chg_cur.aca_max = DEFAULT_ACA_CUR_MAX;
}