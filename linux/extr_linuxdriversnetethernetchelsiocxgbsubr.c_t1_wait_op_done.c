#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ regs; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int t1_wait_op_done(adapter_t *adapter, int reg, u32 mask, int polarity,
			   int attempts, int delay)
{
	while (1) {
		u32 val = readl(adapter->regs + reg) & mask;

		if (!!val == polarity)
			return 0;
		if (--attempts == 0)
			return 1;
		if (delay)
			udelay(delay);
	}
}