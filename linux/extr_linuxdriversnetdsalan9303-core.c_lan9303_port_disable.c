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
struct lan9303 {scalar_t__ phy_addr_base; } ;
struct dsa_switch {struct lan9303* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  lan9303_disable_processing_port (struct lan9303*,int) ; 
 int /*<<< orphan*/  lan9303_phy_write (struct dsa_switch*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan9303_port_disable(struct dsa_switch *ds, int port,
				 struct phy_device *phy)
{
	struct lan9303 *chip = ds->priv;

	lan9303_disable_processing_port(chip, port);
	lan9303_phy_write(ds, chip->phy_addr_base + port, MII_BMCR, BMCR_PDOWN);
}