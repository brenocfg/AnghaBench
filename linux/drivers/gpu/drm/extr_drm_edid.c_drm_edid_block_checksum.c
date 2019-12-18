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

/* Variables and functions */
 int EDID_LENGTH ; 

__attribute__((used)) static int drm_edid_block_checksum(const u8 *raw_edid)
{
	int i;
	u8 csum = 0;
	for (i = 0; i < EDID_LENGTH; i++)
		csum += raw_edid[i];

	return csum;
}