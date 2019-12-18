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
struct emac_instance {int mal_ph; int zmii_ph; int rgmii_ph; int tah_ph; int mdio_ph; scalar_t__ blist; int /*<<< orphan*/  mdio_dev; int /*<<< orphan*/  tah_dev; int /*<<< orphan*/  rgmii_dev; int /*<<< orphan*/  zmii_dev; int /*<<< orphan*/  mal_dev; } ;
struct emac_depentry {int phandle; int /*<<< orphan*/  ofdev; int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  deps ;

/* Variables and functions */
 int EMAC_DEP_COUNT ; 
 size_t EMAC_DEP_MAL_IDX ; 
 size_t EMAC_DEP_MDIO_IDX ; 
 size_t EMAC_DEP_PREV_IDX ; 
 size_t EMAC_DEP_RGMII_IDX ; 
 size_t EMAC_DEP_TAH_IDX ; 
 size_t EMAC_DEP_ZMII_IDX ; 
 int /*<<< orphan*/  EMAC_PROBE_DEP_TIMEOUT ; 
 int ENODEV ; 
 int /*<<< orphan*/  bus_register_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ emac_boot_list ; 
 scalar_t__ emac_check_deps (struct emac_instance*,struct emac_depentry*) ; 
 int /*<<< orphan*/  emac_of_bus_notifier ; 
 int /*<<< orphan*/  emac_probe_wait ; 
 int /*<<< orphan*/  memset (struct emac_depentry**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emac_wait_deps(struct emac_instance *dev)
{
	struct emac_depentry deps[EMAC_DEP_COUNT];
	int i, err;

	memset(&deps, 0, sizeof(deps));

	deps[EMAC_DEP_MAL_IDX].phandle = dev->mal_ph;
	deps[EMAC_DEP_ZMII_IDX].phandle = dev->zmii_ph;
	deps[EMAC_DEP_RGMII_IDX].phandle = dev->rgmii_ph;
	if (dev->tah_ph)
		deps[EMAC_DEP_TAH_IDX].phandle = dev->tah_ph;
	if (dev->mdio_ph)
		deps[EMAC_DEP_MDIO_IDX].phandle = dev->mdio_ph;
	if (dev->blist && dev->blist > emac_boot_list)
		deps[EMAC_DEP_PREV_IDX].phandle = 0xffffffffu;
	bus_register_notifier(&platform_bus_type, &emac_of_bus_notifier);
	wait_event_timeout(emac_probe_wait,
			   emac_check_deps(dev, deps),
			   EMAC_PROBE_DEP_TIMEOUT);
	bus_unregister_notifier(&platform_bus_type, &emac_of_bus_notifier);
	err = emac_check_deps(dev, deps) ? 0 : -ENODEV;
	for (i = 0; i < EMAC_DEP_COUNT; i++) {
		of_node_put(deps[i].node);
		if (err)
			of_dev_put(deps[i].ofdev);
	}
	if (err == 0) {
		dev->mal_dev = deps[EMAC_DEP_MAL_IDX].ofdev;
		dev->zmii_dev = deps[EMAC_DEP_ZMII_IDX].ofdev;
		dev->rgmii_dev = deps[EMAC_DEP_RGMII_IDX].ofdev;
		dev->tah_dev = deps[EMAC_DEP_TAH_IDX].ofdev;
		dev->mdio_dev = deps[EMAC_DEP_MDIO_IDX].ofdev;
	}
	of_dev_put(deps[EMAC_DEP_PREV_IDX].ofdev);
	return err;
}