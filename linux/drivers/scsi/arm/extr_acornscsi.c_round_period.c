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
struct TYPE_2__ {int period_ns; } ;

/* Variables and functions */
 TYPE_1__* sync_xfer_table ; 

__attribute__((used)) static inline
int round_period(unsigned int period)
{
    int i;

    for (i = 1; sync_xfer_table[i].period_ns; i++) {
	if ((period <= sync_xfer_table[i].period_ns) &&
	    (period > sync_xfer_table[i - 1].period_ns))
	    return i;
    }
    return 7;
}