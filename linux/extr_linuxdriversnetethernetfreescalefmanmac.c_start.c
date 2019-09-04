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
struct phy_device {int dummy; } ;
struct mac_priv_s {int (* enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mac_device {int /*<<< orphan*/  fman_mac; struct mac_priv_s* priv; struct phy_device* phy_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_MODE_RX_AND_TX ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start(struct mac_device *mac_dev)
{
	int	 err;
	struct phy_device *phy_dev = mac_dev->phy_dev;
	struct mac_priv_s *priv = mac_dev->priv;

	err = priv->enable(mac_dev->fman_mac, COMM_MODE_RX_AND_TX);
	if (!err && phy_dev)
		phy_start(phy_dev);

	return err;
}