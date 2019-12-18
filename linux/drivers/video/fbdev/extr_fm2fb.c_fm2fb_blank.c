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
struct fb_info {int dummy; } ;

/* Variables and functions */
 unsigned char FRAMEMASTER_ENABLE ; 
 unsigned char FRAMEMASTER_NOLACE ; 
 unsigned char FRAMEMASTER_ROM ; 
 unsigned char* fm2fb_reg ; 

__attribute__((used)) static int fm2fb_blank(int blank, struct fb_info *info)
{
	unsigned char t = FRAMEMASTER_ROM;

	if (!blank)
		t |= FRAMEMASTER_ENABLE | FRAMEMASTER_NOLACE;
	fm2fb_reg[0] = t;
	return 0;
}