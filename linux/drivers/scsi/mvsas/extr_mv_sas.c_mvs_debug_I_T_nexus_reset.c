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
struct sas_phy {int dummy; } ;
struct domain_device {scalar_t__ dev_type; int tproto; } ;

/* Variables and functions */
 int SAS_PROTOCOL_STP ; 
 scalar_t__ SAS_SATA_DEV ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct sas_phy* sas_get_local_phy (struct domain_device*) ; 
 int sas_phy_reset (struct sas_phy*,int) ; 
 int /*<<< orphan*/  sas_put_local_phy (struct sas_phy*) ; 

__attribute__((used)) static int mvs_debug_I_T_nexus_reset(struct domain_device *dev)
{
	int rc;
	struct sas_phy *phy = sas_get_local_phy(dev);
	int reset_type = (dev->dev_type == SAS_SATA_DEV ||
			(dev->tproto & SAS_PROTOCOL_STP)) ? 0 : 1;
	rc = sas_phy_reset(phy, reset_type);
	sas_put_local_phy(phy);
	msleep(2000);
	return rc;
}