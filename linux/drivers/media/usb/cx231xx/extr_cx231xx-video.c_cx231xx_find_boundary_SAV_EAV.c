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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ cx231xx_find_next_SAV_EAV (scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

u8 cx231xx_find_boundary_SAV_EAV(u8 *p_buffer, u8 *partial_buf,
				 u32 *p_bytes_used)
{
	u32 bytes_used;
	u8 boundary_bytes[8];
	u8 sav_eav = 0;

	*p_bytes_used = 0;

	/* Create an array of the last 4 bytes of the last buffer and the first
	   4 bytes of the current buffer. */

	memcpy(boundary_bytes, partial_buf, 4);
	memcpy(boundary_bytes + 4, p_buffer, 4);

	/* Check for the SAV/EAV in the boundary buffer */
	sav_eav = cx231xx_find_next_SAV_EAV((u8 *)&boundary_bytes, 8,
					    &bytes_used);

	if (sav_eav) {
		/* found a boundary SAV/EAV.  Updates the bytes used to reflect
		   only those used in the new buffer */
		*p_bytes_used = bytes_used - 4;
	}

	return sav_eav;
}