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
struct map_pci_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long
intel_dc21285_translate(struct map_pci_info *map, unsigned long ofs)
{
	return ofs & 0x00ffffc0 ? ofs : (ofs ^ (1 << 5));
}