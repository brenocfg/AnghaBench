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
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned long NETDEV_UNREGISTER ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  nfp_flower_free_internal_port_id (struct nfp_app*,struct net_device*) ; 
 scalar_t__ nfp_flower_internal_port_can_offload (struct nfp_app*,struct net_device*) ; 

__attribute__((used)) static int
nfp_flower_internal_port_event_handler(struct nfp_app *app,
				       struct net_device *netdev,
				       unsigned long event)
{
	if (event == NETDEV_UNREGISTER &&
	    nfp_flower_internal_port_can_offload(app, netdev))
		nfp_flower_free_internal_port_id(app, netdev);

	return NOTIFY_OK;
}