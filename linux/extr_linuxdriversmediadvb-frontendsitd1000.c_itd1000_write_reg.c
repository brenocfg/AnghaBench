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
typedef  size_t u8 ;
struct itd1000_state {size_t* shadow; } ;

/* Variables and functions */
 int itd1000_write_regs (struct itd1000_state*,size_t,size_t*,int) ; 

__attribute__((used)) static inline int itd1000_write_reg(struct itd1000_state *state, u8 r, u8 v)
{
	u8 tmp = v; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */
	int ret = itd1000_write_regs(state, r, &tmp, 1);
	state->shadow[r] = tmp;
	return ret;
}