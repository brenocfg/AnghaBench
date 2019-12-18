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
typedef  unsigned int uint32_t ;
struct map_info {int dummy; } ;
struct cfi_private {unsigned int device_type; } ;

/* Variables and functions */
 unsigned int cfi_interleave (struct cfi_private*) ; 
 unsigned int map_bankwidth (struct map_info*) ; 

uint32_t cfi_build_cmd_addr(uint32_t cmd_ofs,
				struct map_info *map, struct cfi_private *cfi)
{
	unsigned bankwidth = map_bankwidth(map);
	unsigned interleave = cfi_interleave(cfi);
	unsigned type = cfi->device_type;
	uint32_t addr;

	addr = (cmd_ofs * type) * interleave;

	/* Modify the unlock address if we are in compatibility mode.
	 * For 16bit devices on 8 bit busses
	 * and 32bit devices on 16 bit busses
	 * set the low bit of the alternating bit sequence of the address.
	 */
	if (((type * interleave) > bankwidth) && ((cmd_ofs & 0xff) == 0xaa))
		addr |= (type >> 1)*interleave;

	return  addr;
}