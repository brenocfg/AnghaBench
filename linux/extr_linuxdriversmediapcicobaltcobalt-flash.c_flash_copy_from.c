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
typedef  int u8 ;
typedef  int u32 ;
struct map_info {int /*<<< orphan*/  virt; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADRS (int) ; 
 int cobalt_bus_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flash_copy_from(struct map_info *map, void *to,
			    unsigned long from, ssize_t len)
{
	u32 src = from;
	u8 *dest = to;
	u32 data;

	while (len) {
		data = cobalt_bus_read32(map->virt, ADRS(src));
		do {
			*dest = data >> (8 * (src & 3));
			src++;
			dest++;
			len--;
		} while (len && (src % 4));
	}
}