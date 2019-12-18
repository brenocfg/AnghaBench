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
struct lan9303_alr_cache_entry {scalar_t__ port_map; } ;
struct lan9303 {struct lan9303_alr_cache_entry* alr_cache; } ;

/* Variables and functions */
 int LAN9303_NUM_ALR_RECORDS ; 

__attribute__((used)) static struct lan9303_alr_cache_entry *
lan9303_alr_cache_find_free(struct lan9303 *chip)
{
	int i;
	struct lan9303_alr_cache_entry *entr = chip->alr_cache;

	for (i = 0; i < LAN9303_NUM_ALR_RECORDS; i++, entr++)
		if (entr->port_map == 0)
			return entr;

	return NULL;
}