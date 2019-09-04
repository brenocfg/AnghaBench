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
struct b44 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int br32 (struct b44*,unsigned long) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,unsigned long,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int b44_wait_bit(struct b44 *bp, unsigned long reg,
			u32 bit, unsigned long timeout, const int clear)
{
	unsigned long i;

	for (i = 0; i < timeout; i++) {
		u32 val = br32(bp, reg);

		if (clear && !(val & bit))
			break;
		if (!clear && (val & bit))
			break;
		udelay(10);
	}
	if (i == timeout) {
		if (net_ratelimit())
			netdev_err(bp->dev, "BUG!  Timeout waiting for bit %08x of register %lx to %s\n",
				   bit, reg, clear ? "clear" : "set");

		return -ENODEV;
	}
	return 0;
}