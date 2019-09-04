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

__attribute__((used)) static int edid_size(const u8 *edid, int data_size)
{
	if (data_size < EDID_LENGTH)
		return 0;

	return (edid[0x7e] + 1) * EDID_LENGTH;
}