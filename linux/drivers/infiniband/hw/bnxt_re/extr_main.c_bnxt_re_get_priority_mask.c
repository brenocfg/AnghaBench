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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct dcb_app {int /*<<< orphan*/  protocol; int /*<<< orphan*/  selector; } ;
struct bnxt_re_dev {struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  app ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IBOE ; 
 int /*<<< orphan*/  IEEE_8021QAZ_APP_SEL_DGRAM ; 
 int /*<<< orphan*/  IEEE_8021QAZ_APP_SEL_ETHERTYPE ; 
 int /*<<< orphan*/  ROCE_V2_UDP_DPORT ; 
 int /*<<< orphan*/  dcb_ieee_getapp_mask (struct net_device*,struct dcb_app*) ; 
 int /*<<< orphan*/  memset (struct dcb_app*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 bnxt_re_get_priority_mask(struct bnxt_re_dev *rdev)
{
	u32 prio_map = 0, tmp_map = 0;
	struct net_device *netdev;
	struct dcb_app app;

	netdev = rdev->netdev;

	memset(&app, 0, sizeof(app));
	app.selector = IEEE_8021QAZ_APP_SEL_ETHERTYPE;
	app.protocol = ETH_P_IBOE;
	tmp_map = dcb_ieee_getapp_mask(netdev, &app);
	prio_map = tmp_map;

	app.selector = IEEE_8021QAZ_APP_SEL_DGRAM;
	app.protocol = ROCE_V2_UDP_DPORT;
	tmp_map = dcb_ieee_getapp_mask(netdev, &app);
	prio_map |= tmp_map;

	return prio_map;
}