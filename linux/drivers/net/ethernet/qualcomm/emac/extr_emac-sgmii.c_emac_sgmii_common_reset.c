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
struct emac_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int emac_sgmii_init (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_link_init (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_sgmii_reset_prepare (struct emac_adapter*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void emac_sgmii_common_reset(struct emac_adapter *adpt)
{
	int ret;

	emac_sgmii_reset_prepare(adpt);
	emac_sgmii_link_init(adpt);

	ret = emac_sgmii_init(adpt);
	if (ret)
		netdev_err(adpt->netdev,
			   "could not reinitialize internal PHY (error=%i)\n",
			   ret);
}