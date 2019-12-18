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
struct wil6210_vif {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_vif_deinit (struct wil6210_vif*) ; 

void wil_vif_free(struct wil6210_vif *vif)
{
	struct net_device *ndev = vif_to_ndev(vif);

	wil_vif_deinit(vif);
	free_netdev(ndev);
}