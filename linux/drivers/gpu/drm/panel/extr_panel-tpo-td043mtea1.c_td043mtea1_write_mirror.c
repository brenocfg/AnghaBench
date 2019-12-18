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
struct td043mtea1_panel {scalar_t__ vmirror; } ;

/* Variables and functions */
 int TPO_R04_CP_CLK_FREQ_1H ; 
 int TPO_R04_NFLIP_H ; 
 int TPO_R04_NFLIP_V ; 
 int TPO_R04_VGL_FREQ_1H ; 
 int td043mtea1_write (struct td043mtea1_panel*,int,int) ; 

__attribute__((used)) static int td043mtea1_write_mirror(struct td043mtea1_panel *lcd)
{
	u8 reg4 = TPO_R04_NFLIP_H | TPO_R04_NFLIP_V |
		TPO_R04_CP_CLK_FREQ_1H | TPO_R04_VGL_FREQ_1H;
	if (lcd->vmirror)
		reg4 &= ~TPO_R04_NFLIP_V;

	return td043mtea1_write(lcd, 4, reg4);
}