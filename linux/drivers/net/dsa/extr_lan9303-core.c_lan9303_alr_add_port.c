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
struct lan9303_alr_cache_entry {int stp_override; int /*<<< orphan*/  port_map; int /*<<< orphan*/  mac_addr; } ;
struct lan9303 {int /*<<< orphan*/  alr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct lan9303_alr_cache_entry* lan9303_alr_cache_find_free (struct lan9303*) ; 
 struct lan9303_alr_cache_entry* lan9303_alr_cache_find_mac (struct lan9303*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lan9303_alr_set_entry (struct lan9303*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan9303_alr_add_port(struct lan9303 *chip, const u8 *mac, int port,
				bool stp_override)
{
	struct lan9303_alr_cache_entry *entr;

	mutex_lock(&chip->alr_mutex);
	entr = lan9303_alr_cache_find_mac(chip, mac);
	if (!entr) { /*New entry */
		entr = lan9303_alr_cache_find_free(chip);
		if (!entr) {
			mutex_unlock(&chip->alr_mutex);
			return -ENOSPC;
		}
		ether_addr_copy(entr->mac_addr, mac);
	}
	entr->port_map |= BIT(port);
	entr->stp_override = stp_override;
	lan9303_alr_set_entry(chip, mac, entr->port_map, stp_override);
	mutex_unlock(&chip->alr_mutex);

	return 0;
}