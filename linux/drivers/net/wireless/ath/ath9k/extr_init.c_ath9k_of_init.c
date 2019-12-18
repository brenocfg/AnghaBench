#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct ath_softc {struct ath_hw* sc_ah; TYPE_2__* dev; } ;
struct ath_hw {int /*<<< orphan*/  ah_flags; int /*<<< orphan*/  dev; } ;
struct ath_common {int /*<<< orphan*/  macaddr; TYPE_1__* bus_ops; } ;
typedef  enum ath_bus_type { ____Placeholder_ath_bus_type } ath_bus_type ;
typedef  int /*<<< orphan*/  eeprom_name ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_3__ {int ath_bus_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_NO_EEP_SWAP ; 
 int /*<<< orphan*/  AH_USE_EEPROM ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  IS_ERR (char const*) ; 
 int ath9k_eeprom_request (struct ath_softc*,char*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_bus_type_to_string (int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 char* of_get_mac_address (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_of_init(struct ath_softc *sc)
{
	struct device_node *np = sc->dev->of_node;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	enum ath_bus_type bus_type = common->bus_ops->ath_bus_type;
	const char *mac;
	char eeprom_name[100];
	int ret;

	if (!of_device_is_available(np))
		return 0;

	ath_dbg(common, CONFIG, "parsing configuration from OF node\n");

	if (of_property_read_bool(np, "qca,no-eeprom")) {
		/* ath9k-eeprom-<bus>-<id>.bin */
		scnprintf(eeprom_name, sizeof(eeprom_name),
			  "ath9k-eeprom-%s-%s.bin",
			  ath_bus_type_to_string(bus_type), dev_name(ah->dev));

		ret = ath9k_eeprom_request(sc, eeprom_name);
		if (ret)
			return ret;

		ah->ah_flags &= ~AH_USE_EEPROM;
		ah->ah_flags |= AH_NO_EEP_SWAP;
	}

	mac = of_get_mac_address(np);
	if (!IS_ERR(mac))
		ether_addr_copy(common->macaddr, mac);

	return 0;
}