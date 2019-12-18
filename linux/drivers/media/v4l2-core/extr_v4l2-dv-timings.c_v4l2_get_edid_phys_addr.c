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
typedef  int const u16 ;

/* Variables and functions */
 int const CEC_PHYS_ADDR_INVALID ; 
 unsigned int cec_get_edid_spa_location (int const*,unsigned int) ; 

u16 v4l2_get_edid_phys_addr(const u8 *edid, unsigned int size,
			    unsigned int *offset)
{
	unsigned int loc = cec_get_edid_spa_location(edid, size);

	if (offset)
		*offset = loc;
	if (loc == 0)
		return CEC_PHYS_ADDR_INVALID;
	return (edid[loc] << 8) | edid[loc + 1];
}