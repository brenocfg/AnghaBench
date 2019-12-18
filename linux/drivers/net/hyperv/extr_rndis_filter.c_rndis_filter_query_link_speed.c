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
typedef  int u32 ;
struct rndis_device {int /*<<< orphan*/  ndev; } ;
struct netvsc_device {int dummy; } ;
struct net_device_context {int speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_OID_GEN_LINK_SPEED ; 
 struct net_device_context* netdev_priv (int /*<<< orphan*/ ) ; 
 int rndis_filter_query_device (struct rndis_device*,struct netvsc_device*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int rndis_filter_query_link_speed(struct rndis_device *dev,
					 struct netvsc_device *net_device)
{
	u32 size = sizeof(u32);
	u32 link_speed;
	struct net_device_context *ndc;
	int ret;

	ret = rndis_filter_query_device(dev, net_device,
					RNDIS_OID_GEN_LINK_SPEED,
					&link_speed, &size);

	if (!ret) {
		ndc = netdev_priv(dev->ndev);

		/* The link speed reported from host is in 100bps unit, so
		 * we convert it to Mbps here.
		 */
		ndc->speed = link_speed / 10000;
	}

	return ret;
}