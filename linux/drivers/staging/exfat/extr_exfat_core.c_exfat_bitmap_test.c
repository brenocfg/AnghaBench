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
typedef  int s32 ;

/* Variables and functions */
 size_t BITMAP_LOC (int) ; 
 int BITMAP_SHIFT (int) ; 

__attribute__((used)) static inline s32 exfat_bitmap_test(u8 *bitmap, int i)
{
	u8 data;

	data = bitmap[BITMAP_LOC(i)];
	if ((data >> BITMAP_SHIFT(i)) & 0x01)
		return 1;
	return 0;
}