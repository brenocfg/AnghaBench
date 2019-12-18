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
struct tridentfb_par {int eng_oper; } ;

/* Variables and functions */
 int DRAWFL ; 
 int OLDCMD ; 
 int OLDDIM ; 
 int OLDDST ; 
 int ROP_P ; 
 int point (int,int) ; 
 int /*<<< orphan*/  t_outb (struct tridentfb_par*,int,int) ; 
 int /*<<< orphan*/  writemmr (struct tridentfb_par*,int,int) ; 

__attribute__((used)) static void xp_fill_rect(struct tridentfb_par *par,
			 u32 x, u32 y, u32 w, u32 h, u32 c, u32 rop)
{
	writemmr(par, 0x2127, ROP_P);
	writemmr(par, 0x2158, c);
	writemmr(par, DRAWFL, 0x4000);
	writemmr(par, OLDDIM, point(h, w));
	writemmr(par, OLDDST, point(y, x));
	t_outb(par, 0x01, OLDCMD);
	t_outb(par, par->eng_oper, 0x2125);
}