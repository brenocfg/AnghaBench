#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int clock; } ;
struct mmc_host {int actual_clock; TYPE_1__ ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static unsigned int mmc_blk_clock_khz(struct mmc_host *host)
{
	if (host->actual_clock)
		return host->actual_clock / 1000;

	/* Clock may be subject to a divisor, fudge it by a factor of 2. */
	if (host->ios.clock)
		return host->ios.clock / 2000;

	/* How can there be no clock */
	WARN_ON_ONCE(1);
	return 100; /* 100 kHz is minimum possible value */
}