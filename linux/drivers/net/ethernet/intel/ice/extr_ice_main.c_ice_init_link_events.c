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
typedef  int /*<<< orphan*/  u16 ;
struct ice_port_info {int /*<<< orphan*/  lport; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int EIO ; 
 int ICE_AQ_LINK_EVENT_MEDIA_NA ; 
 int ICE_AQ_LINK_EVENT_MODULE_QUAL_FAIL ; 
 int ICE_AQ_LINK_EVENT_UPDOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_aq_get_link_info (struct ice_port_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ice_aq_set_event_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_hw_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_init_link_events(struct ice_port_info *pi)
{
	u16 mask;

	mask = ~((u16)(ICE_AQ_LINK_EVENT_UPDOWN | ICE_AQ_LINK_EVENT_MEDIA_NA |
		       ICE_AQ_LINK_EVENT_MODULE_QUAL_FAIL));

	if (ice_aq_set_event_mask(pi->hw, pi->lport, mask, NULL)) {
		dev_dbg(ice_hw_to_dev(pi->hw),
			"Failed to set link event mask for port %d\n",
			pi->lport);
		return -EIO;
	}

	if (ice_aq_get_link_info(pi, true, NULL, NULL)) {
		dev_dbg(ice_hw_to_dev(pi->hw),
			"Failed to enable link events for port %d\n",
			pi->lport);
		return -EIO;
	}

	return 0;
}