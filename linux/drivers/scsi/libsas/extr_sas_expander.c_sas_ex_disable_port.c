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
typedef  int /*<<< orphan*/  u8 ;
struct expander_device {int num_phys; struct ex_phy* ex_phy; } ;
struct ex_phy {scalar_t__ phy_state; int /*<<< orphan*/ * attached_sas_addr; } ;
struct domain_device {struct expander_device ex_dev; } ;

/* Variables and functions */
 scalar_t__ PHY_NOT_PRESENT ; 
 scalar_t__ PHY_VACANT ; 
 scalar_t__ SAS_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_ex_disable_phy (struct domain_device*,int) ; 

__attribute__((used)) static void sas_ex_disable_port(struct domain_device *dev, u8 *sas_addr)
{
	struct expander_device *ex = &dev->ex_dev;
	int i;

	for (i = 0; i < ex->num_phys; i++) {
		struct ex_phy *phy = &ex->ex_phy[i];

		if (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PRESENT)
			continue;

		if (SAS_ADDR(phy->attached_sas_addr) == SAS_ADDR(sas_addr))
			sas_ex_disable_phy(dev, i);
	}
}