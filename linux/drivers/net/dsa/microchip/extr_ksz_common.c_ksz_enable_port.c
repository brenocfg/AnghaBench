#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int dummy; } ;
struct ksz_device {TYPE_1__* dev_ops; } ;
struct dsa_switch {struct ksz_device* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_setup ) (struct ksz_device*,int,struct phy_device*) ;int /*<<< orphan*/  (* port_setup ) (struct ksz_device*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  stub1 (struct ksz_device*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ksz_device*,int,struct phy_device*) ; 

int ksz_enable_port(struct dsa_switch *ds, int port, struct phy_device *phy)
{
	struct ksz_device *dev = ds->priv;

	if (!dsa_is_user_port(ds, port))
		return 0;

	/* setup slave port */
	dev->dev_ops->port_setup(dev, port, false);
	if (dev->dev_ops->phy_setup)
		dev->dev_ops->phy_setup(dev, port, phy);

	/* port_stp_state_set() will be called after to enable the port so
	 * there is no need to do anything.
	 */

	return 0;
}