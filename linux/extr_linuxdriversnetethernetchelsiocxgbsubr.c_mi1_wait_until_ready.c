#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int F_MI1_OP_BUSY ; 
 int /*<<< orphan*/  __t1_tpi_read (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mi1_wait_until_ready(adapter_t *adapter, int mi1_reg)
{
	int attempts = 100, busy;

	do {
		u32 val;

		__t1_tpi_read(adapter, mi1_reg, &val);
		busy = val & F_MI1_OP_BUSY;
		if (busy)
			udelay(10);
	} while (busy && --attempts);
	if (busy)
		pr_alert("%s: MDIO operation timed out\n", adapter->name);
	return busy;
}