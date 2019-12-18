#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct dcb_table {int entries; TYPE_1__* entry; } ;
struct nvbios {int /*<<< orphan*/  dev; struct dcb_table dcb; } ;
struct TYPE_2__ {int connector; int i2c_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_match_device (int /*<<< orphan*/ ,int,int,int) ; 
 int* olddcb_conntab (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dcb_fake_connectors(struct nvbios *bios)
{
	struct dcb_table *dcbt = &bios->dcb;
	u8 map[16] = { };
	int i, idx = 0;

	/* heuristic: if we ever get a non-zero connector field, assume
	 * that all the indices are valid and we don't need fake them.
	 *
	 * and, as usual, a blacklist of boards with bad bios data..
	 */
	if (!nv_match_device(bios->dev, 0x0392, 0x107d, 0x20a2)) {
		for (i = 0; i < dcbt->entries; i++) {
			if (dcbt->entry[i].connector)
				return;
		}
	}

	/* no useful connector info available, we need to make it up
	 * ourselves.  the rule here is: anything on the same i2c bus
	 * is considered to be on the same connector.  any output
	 * without an associated i2c bus is assigned its own unique
	 * connector index.
	 */
	for (i = 0; i < dcbt->entries; i++) {
		u8 i2c = dcbt->entry[i].i2c_index;
		if (i2c == 0x0f) {
			dcbt->entry[i].connector = idx++;
		} else {
			if (!map[i2c])
				map[i2c] = ++idx;
			dcbt->entry[i].connector = map[i2c] - 1;
		}
	}

	/* if we created more than one connector, destroy the connector
	 * table - just in case it has random, rather than stub, entries.
	 */
	if (i > 1) {
		u8 *conntab = olddcb_conntab(bios->dev);
		if (conntab)
			conntab[0] = 0x00;
	}
}