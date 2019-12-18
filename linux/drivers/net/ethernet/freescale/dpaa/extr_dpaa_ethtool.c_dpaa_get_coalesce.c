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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qman_portal {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int use_adaptive_rx_coalesce; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  qman_dqrr_get_ithresh (struct qman_portal*,int /*<<< orphan*/ *) ; 
 struct qman_portal* qman_get_affine_portal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qman_portal_get_iperiod (struct qman_portal*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int dpaa_get_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *c)
{
	struct qman_portal *portal;
	u32 period;
	u8 thresh;

	portal = qman_get_affine_portal(smp_processor_id());
	qman_portal_get_iperiod(portal, &period);
	qman_dqrr_get_ithresh(portal, &thresh);

	c->rx_coalesce_usecs = period;
	c->rx_max_coalesced_frames = thresh;
	c->use_adaptive_rx_coalesce = false;

	return 0;
}