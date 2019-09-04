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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ DCA_TAG_MAP_VALID ; 

__attribute__((used)) static inline int dca3_tag_map_invalid(u8 *tag_map)
{
	/*
	 * If the tag map is not programmed by the BIOS the default is:
	 * 0x80 0x80 0x80 0x80 0x80 0x00 0x00 0x00
	 *
	 * This an invalid map and will result in only 2 possible tags
	 * 0x1F and 0x00.  0x00 is an invalid DCA tag so we know that
	 * this entire definition is invalid.
	 */
	return ((tag_map[0] == DCA_TAG_MAP_VALID) &&
		(tag_map[1] == DCA_TAG_MAP_VALID) &&
		(tag_map[2] == DCA_TAG_MAP_VALID) &&
		(tag_map[3] == DCA_TAG_MAP_VALID) &&
		(tag_map[4] == DCA_TAG_MAP_VALID));
}