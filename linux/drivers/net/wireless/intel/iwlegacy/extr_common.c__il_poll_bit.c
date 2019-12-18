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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int _il_rd (struct il_priv*,int) ; 
 int /*<<< orphan*/  udelay (int const) ; 

int
_il_poll_bit(struct il_priv *il, u32 addr, u32 bits, u32 mask, int timeout)
{
	const int interval = 10; /* microseconds */
	int t = 0;

	do {
		if ((_il_rd(il, addr) & mask) == (bits & mask))
			return t;
		udelay(interval);
		t += interval;
	} while (t < timeout);

	return -ETIMEDOUT;
}