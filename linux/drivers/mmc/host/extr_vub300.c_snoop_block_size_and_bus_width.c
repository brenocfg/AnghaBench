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
struct vub300_mmc_host {int* fbs; int bus_width; } ;

/* Variables and functions */

__attribute__((used)) static void snoop_block_size_and_bus_width(struct vub300_mmc_host *vub300,
					   u32 cmd_arg)
{
	if ((0xFBFFFE00 & cmd_arg) == 0x80022200)
		vub300->fbs[1] = (cmd_arg << 8) | (0x00FF & vub300->fbs[1]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x80022000)
		vub300->fbs[1] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[1]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x80042200)
		vub300->fbs[2] = (cmd_arg << 8) | (0x00FF & vub300->fbs[2]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x80042000)
		vub300->fbs[2] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[2]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x80062200)
		vub300->fbs[3] = (cmd_arg << 8) | (0x00FF & vub300->fbs[3]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x80062000)
		vub300->fbs[3] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[3]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x80082200)
		vub300->fbs[4] = (cmd_arg << 8) | (0x00FF & vub300->fbs[4]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x80082000)
		vub300->fbs[4] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[4]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x800A2200)
		vub300->fbs[5] = (cmd_arg << 8) | (0x00FF & vub300->fbs[5]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x800A2000)
		vub300->fbs[5] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[5]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x800C2200)
		vub300->fbs[6] = (cmd_arg << 8) | (0x00FF & vub300->fbs[6]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x800C2000)
		vub300->fbs[6] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[6]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x800E2200)
		vub300->fbs[7] = (cmd_arg << 8) | (0x00FF & vub300->fbs[7]);
	else if ((0xFBFFFE00 & cmd_arg) == 0x800E2000)
		vub300->fbs[7] = (0xFF & cmd_arg) | (0xFF00 & vub300->fbs[7]);
	else if ((0xFBFFFE03 & cmd_arg) == 0x80000E00)
		vub300->bus_width = 1;
	else if ((0xFBFFFE03 & cmd_arg) == 0x80000E02)
		vub300->bus_width = 4;
}