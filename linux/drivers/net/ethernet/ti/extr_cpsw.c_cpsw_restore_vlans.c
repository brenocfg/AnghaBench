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
struct cpsw_priv {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpsw_ndo_vlan_rx_add_vid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpsw_restore_vlans(struct net_device *vdev, int vid, void *arg)
{
	struct cpsw_priv *priv = arg;

	if (!vdev)
		return 0;

	cpsw_ndo_vlan_rx_add_vid(priv->ndev, 0, vid);
	return 0;
}