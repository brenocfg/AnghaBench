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
struct n2rng {int /*<<< orphan*/  wd_timeo; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int EWOULDBLOCK ; 
 unsigned long HV_EBUSY ; 
 unsigned long HV_EOK ; 
 unsigned long HV_EWOULDBLOCK ; 
 int N2RNG_BLOCK_LIMIT ; 
 int N2RNG_BUSY_LIMIT ; 
 int /*<<< orphan*/  __delay (unsigned long) ; 
 unsigned long n2rng_write_ctl_one (struct n2rng*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int n2rng_generic_write_control(struct n2rng *np,
				       unsigned long control_ra,
				       unsigned long unit,
				       unsigned long state)
{
	unsigned long hv_err, ticks;
	int block = 0, busy = 0;

	while (1) {
		hv_err = n2rng_write_ctl_one(np, unit, state, control_ra,
					     np->wd_timeo, &ticks);
		if (hv_err == HV_EOK)
			return 0;

		if (hv_err == HV_EWOULDBLOCK) {
			if (++block >= N2RNG_BLOCK_LIMIT)
				return -EWOULDBLOCK;
			__delay(ticks);
		} else if (hv_err == HV_EBUSY) {
			if (++busy >= N2RNG_BUSY_LIMIT)
				return -EBUSY;
			udelay(1);
		} else
			return -ENODEV;
	}
}