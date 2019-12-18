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
struct tridentfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCModuleTest ; 
 int /*<<< orphan*/  CRTHiOrd ; 
 int /*<<< orphan*/  VGA_CRTC_START_HI ; 
 int /*<<< orphan*/  VGA_CRTC_START_LO ; 
 int read3X4 (struct tridentfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write3X4 (struct tridentfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_screen_start(struct tridentfb_par *par, int base)
{
	u8 tmp;
	write3X4(par, VGA_CRTC_START_LO, base & 0xFF);
	write3X4(par, VGA_CRTC_START_HI, (base & 0xFF00) >> 8);
	tmp = read3X4(par, CRTCModuleTest) & 0xDF;
	write3X4(par, CRTCModuleTest, tmp | ((base & 0x10000) >> 11));
	tmp = read3X4(par, CRTHiOrd) & 0xF8;
	write3X4(par, CRTHiOrd, tmp | ((base & 0xE0000) >> 17));
}