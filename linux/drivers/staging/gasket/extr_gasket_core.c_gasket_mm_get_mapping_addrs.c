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
typedef  scalar_t__ ulong ;
struct gasket_mappable_region {scalar_t__ start; scalar_t__ length_bytes; } ;

/* Variables and functions */
 void* min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
gasket_mm_get_mapping_addrs(const struct gasket_mappable_region *region,
			    ulong bar_offset, ulong requested_length,
			    struct gasket_mappable_region *mappable_region,
			    ulong *virt_offset)
{
	ulong range_start = region->start;
	ulong range_length = region->length_bytes;
	ulong range_end = range_start + range_length;

	*virt_offset = 0;
	if (bar_offset + requested_length < range_start) {
		/*
		 * If the requested region is completely below the range,
		 * there is nothing to map.
		 */
		return false;
	} else if (bar_offset <= range_start) {
		/* If the bar offset is below this range's start
		 * but the requested length continues into it:
		 * 1) Only map starting from the beginning of this
		 *      range's phys. offset, so we don't map unmappable
		 *	memory.
		 * 2) The length of the virtual memory to not map is the
		 *	delta between the bar offset and the
		 *	mappable start (and since the mappable start is
		 *	bigger, start - req.)
		 * 3) The map length is the minimum of the mappable
		 *	requested length (requested_length - virt_offset)
		 *	and the actual mappable length of the range.
		 */
		mappable_region->start = range_start;
		*virt_offset = range_start - bar_offset;
		mappable_region->length_bytes =
			min(requested_length - *virt_offset, range_length);
		return true;
	} else if (bar_offset > range_start &&
		   bar_offset < range_end) {
		/*
		 * If the bar offset is within this range:
		 * 1) Map starting from the bar offset.
		 * 2) Because there is no forbidden memory between the
		 *	bar offset and the range start,
		 *	virt_offset is 0.
		 * 3) The map length is the minimum of the requested
		 *	length and the remaining length in the buffer
		 *	(range_end - bar_offset)
		 */
		mappable_region->start = bar_offset;
		*virt_offset = 0;
		mappable_region->length_bytes =
			min(requested_length, range_end - bar_offset);
		return true;
	}

	/*
	 * If the requested [start] offset is above range_end,
	 * there's nothing to map.
	 */
	return false;
}