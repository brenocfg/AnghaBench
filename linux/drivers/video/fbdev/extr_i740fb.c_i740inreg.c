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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct i740fb_par {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  vga_mm_r (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vga_mm_w (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 i740inreg(struct i740fb_par *par, u16 port, u8 reg)
{
	vga_mm_w(par->regs, port, reg);
	return vga_mm_r(par->regs, port+1);
}