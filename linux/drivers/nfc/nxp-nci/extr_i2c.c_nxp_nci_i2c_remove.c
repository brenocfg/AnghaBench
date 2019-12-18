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
struct nxp_nci_i2c_phy {int /*<<< orphan*/  ndev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct nxp_nci_i2c_phy*) ; 
 struct nxp_nci_i2c_phy* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  nxp_nci_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxp_nci_i2c_remove(struct i2c_client *client)
{
	struct nxp_nci_i2c_phy *phy = i2c_get_clientdata(client);

	nxp_nci_remove(phy->ndev);
	free_irq(client->irq, phy);

	return 0;
}