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
struct nvidia_par {int /*<<< orphan*/  PCIO; } ;

/* Variables and functions */
 int VGA_RD08 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int,int) ; 

void NVLockUnlock(struct nvidia_par *par, int Lock)
{
	u8 cr11;

	VGA_WR08(par->PCIO, 0x3D4, 0x1F);
	VGA_WR08(par->PCIO, 0x3D5, Lock ? 0x99 : 0x57);

	VGA_WR08(par->PCIO, 0x3D4, 0x11);
	cr11 = VGA_RD08(par->PCIO, 0x3D5);
	if (Lock)
		cr11 |= 0x80;
	else
		cr11 &= ~0x80;
	VGA_WR08(par->PCIO, 0x3D5, cr11);
}