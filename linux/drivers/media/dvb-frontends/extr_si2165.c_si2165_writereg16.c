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
typedef  int u16 ;
struct si2165_state {int dummy; } ;

/* Variables and functions */
 int si2165_write (struct si2165_state*,int const,int*,int) ; 

__attribute__((used)) static int si2165_writereg16(struct si2165_state *state, const u16 reg, u16 val)
{
	u8 buf[2] = { val & 0xff, (val >> 8) & 0xff };

	return si2165_write(state, reg, buf, 2);
}