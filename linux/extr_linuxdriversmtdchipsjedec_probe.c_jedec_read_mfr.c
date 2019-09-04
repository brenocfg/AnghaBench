#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  unsigned long u32 ;
struct map_info {scalar_t__ size; } ;
struct cfi_private {int device_type; } ;
struct TYPE_3__ {unsigned long* x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 unsigned long CFI_MFR_CONTINUATION ; 
 scalar_t__ cfi_build_cmd_addr (scalar_t__,struct map_info*,struct cfi_private*) ; 
 TYPE_1__ map_read (struct map_info*,scalar_t__) ; 

__attribute__((used)) static inline u32 jedec_read_mfr(struct map_info *map, uint32_t base,
	struct cfi_private *cfi)
{
	map_word result;
	unsigned long mask;
	int bank = 0;

	/* According to JEDEC "Standard Manufacturer's Identification Code"
	 * (http://www.jedec.org/download/search/jep106W.pdf)
	 * several first banks can contain 0x7f instead of actual ID
	 */
	do {
		uint32_t ofs = cfi_build_cmd_addr(0 + (bank << 8), map, cfi);
		mask = (1 << (cfi->device_type * 8)) - 1;
		if (ofs >= map->size)
			return 0;
		result = map_read(map, base + ofs);
		bank++;
	} while ((result.x[0] & mask) == CFI_MFR_CONTINUATION);

	return result.x[0] & mask;
}