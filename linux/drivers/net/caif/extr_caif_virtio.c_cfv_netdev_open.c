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
struct net_device {int dummy; } ;
struct cfv_info {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ cfv_create_genpool (struct cfv_info*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct cfv_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static int cfv_netdev_open(struct net_device *netdev)
{
	struct cfv_info *cfv = netdev_priv(netdev);

	if (cfv_create_genpool(cfv))
		return -ENOMEM;

	netif_carrier_on(netdev);
	napi_enable(&cfv->napi);

	/* Schedule NAPI to read any pending packets */
	napi_schedule(&cfv->napi);
	return 0;
}