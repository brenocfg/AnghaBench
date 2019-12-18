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
union cvmx_smix_en {scalar_t__ u64; } ;
struct platform_device {int dummy; } ;
struct cavium_mdiobus {scalar_t__ register_base; int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 scalar_t__ SMI_EN ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oct_mdio_writeq (scalar_t__,scalar_t__) ; 
 struct cavium_mdiobus* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int octeon_mdiobus_remove(struct platform_device *pdev)
{
	struct cavium_mdiobus *bus;
	union cvmx_smix_en smi_en;

	bus = platform_get_drvdata(pdev);

	mdiobus_unregister(bus->mii_bus);
	mdiobus_free(bus->mii_bus);
	smi_en.u64 = 0;
	oct_mdio_writeq(smi_en.u64, bus->register_base + SMI_EN);
	return 0;
}