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

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void _spi_transfer_delay_ns(u32 ns)
{
	if (!ns)
		return;
	if (ns <= 1000) {
		ndelay(ns);
	} else {
		u32 us = DIV_ROUND_UP(ns, 1000);

		if (us <= 10)
			udelay(us);
		else
			usleep_range(us, us + DIV_ROUND_UP(us, 10));
	}
}