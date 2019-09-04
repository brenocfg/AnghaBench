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
struct wbsd_host {int config; int unlock_code; int chip_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  WBSD_CONF_ID_HI ; 
 int /*<<< orphan*/  WBSD_CONF_ID_LO ; 
 int* config_ports ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 
 int* unlock_codes ; 
 int* valid_ids ; 
 int /*<<< orphan*/  wbsd_lock_config (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_unlock_config (struct wbsd_host*) ; 

__attribute__((used)) static int wbsd_scan(struct wbsd_host *host)
{
	int i, j, k;
	int id;

	/*
	 * Iterate through all ports, all codes to
	 * find hardware that is in our known list.
	 */
	for (i = 0; i < ARRAY_SIZE(config_ports); i++) {
		if (!request_region(config_ports[i], 2, DRIVER_NAME))
			continue;

		for (j = 0; j < ARRAY_SIZE(unlock_codes); j++) {
			id = 0xFFFF;

			host->config = config_ports[i];
			host->unlock_code = unlock_codes[j];

			wbsd_unlock_config(host);

			outb(WBSD_CONF_ID_HI, config_ports[i]);
			id = inb(config_ports[i] + 1) << 8;

			outb(WBSD_CONF_ID_LO, config_ports[i]);
			id |= inb(config_ports[i] + 1);

			wbsd_lock_config(host);

			for (k = 0; k < ARRAY_SIZE(valid_ids); k++) {
				if (id == valid_ids[k]) {
					host->chip_id = id;

					return 0;
				}
			}

			if (id != 0xFFFF) {
				DBG("Unknown hardware (id %x) found at %x\n",
					id, config_ports[i]);
			}
		}

		release_region(config_ports[i], 2);
	}

	host->config = 0;
	host->unlock_code = 0;

	return -ENODEV;
}