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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int cx18_read_reg (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int,int,int) ; 

int cx18_av_write_expect(struct cx18 *cx, u16 addr, u8 value, u8 eval, u8 mask)
{
	u32 reg = 0xc40000 + (addr & ~3);
	int shift = (addr & 3) * 8;
	u32 x = cx18_read_reg(cx, reg);

	x = (x & ~((u32)0xff << shift)) | ((u32)value << shift);
	cx18_write_reg_expect(cx, x, reg,
				((u32)eval << shift), ((u32)mask << shift));
	return 0;
}