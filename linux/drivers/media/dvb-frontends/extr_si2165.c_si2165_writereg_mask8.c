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
typedef  int /*<<< orphan*/  u16 ;
struct si2165_state {int dummy; } ;

/* Variables and functions */
 int si2165_readreg8 (struct si2165_state*,int /*<<< orphan*/  const,int*) ; 
 int si2165_writereg8 (struct si2165_state*,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static int si2165_writereg_mask8(struct si2165_state *state, const u16 reg,
				 u8 val, u8 mask)
{
	if (mask != 0xff) {
		u8 tmp;
		int ret = si2165_readreg8(state, reg, &tmp);

		if (ret < 0)
			return ret;

		val &= mask;
		tmp &= ~mask;
		val |= tmp;
	}
	return si2165_writereg8(state, reg, val);
}