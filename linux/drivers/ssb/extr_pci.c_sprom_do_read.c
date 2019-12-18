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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_bus {int sprom_size; scalar_t__ sprom_offset; scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 

__attribute__((used)) static int sprom_do_read(struct ssb_bus *bus, u16 *sprom)
{
	int i;

	for (i = 0; i < bus->sprom_size; i++)
		sprom[i] = ioread16(bus->mmio + bus->sprom_offset + (i * 2));

	return 0;
}