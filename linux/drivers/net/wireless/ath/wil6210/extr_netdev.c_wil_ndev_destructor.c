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
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  wil_vif_deinit (struct wil6210_vif*) ; 

__attribute__((used)) static void wil_ndev_destructor(struct net_device *ndev)
{
	struct wil6210_vif *vif = ndev_to_vif(ndev);

	wil_vif_deinit(vif);
}