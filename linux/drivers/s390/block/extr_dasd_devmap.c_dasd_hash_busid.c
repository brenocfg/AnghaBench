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

/* Variables and functions */
 int DASD_BUS_ID_SIZE ; 

__attribute__((used)) static inline int
dasd_hash_busid(const char *bus_id)
{
	int hash, i;

	hash = 0;
	for (i = 0; (i < DASD_BUS_ID_SIZE) && *bus_id; i++, bus_id++)
		hash += *bus_id;
	return hash & 0xff;
}