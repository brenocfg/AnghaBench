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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HD64461_BBTDHR ; 
 int /*<<< orphan*/  HD64461_BBTDSARH ; 
 int /*<<< orphan*/  HD64461_BBTDSARL ; 
 int /*<<< orphan*/  HD64461_BBTDWR ; 
 int WIDTH ; 
 int /*<<< orphan*/  fb_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hitfb_accel_set_dest(int truecolor, u16 dx, u16 dy,
					u16 width, u16 height)
{
	u32 saddr = WIDTH * dy + dx;
	if (truecolor)
		saddr <<= 1;

	fb_writew(width-1, HD64461_BBTDWR);
	fb_writew(height-1, HD64461_BBTDHR);

	fb_writew(saddr & 0xffff, HD64461_BBTDSARL);
	fb_writew(saddr >> 16, HD64461_BBTDSARH);

}