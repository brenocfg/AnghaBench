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
 int DIV_ROUND_CLOSEST (long,long) ; 
 int /*<<< orphan*/  IOC_IRQREQA ; 
 int /*<<< orphan*/  IOC_T0CNTH ; 
 int /*<<< orphan*/  IOC_T0CNTL ; 
 int /*<<< orphan*/  IOC_T0LATCH ; 
 long RPC_LATCH ; 
 int /*<<< orphan*/  barrier () ; 
 int ioc_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tick_nsec ; 

__attribute__((used)) static u32 ioc_timer_gettimeoffset(void)
{
	unsigned int count1, count2, status;
	long offset;

	ioc_writeb (0, IOC_T0LATCH);
	barrier ();
	count1 = ioc_readb(IOC_T0CNTL) | (ioc_readb(IOC_T0CNTH) << 8);
	barrier ();
	status = ioc_readb(IOC_IRQREQA);
	barrier ();
	ioc_writeb (0, IOC_T0LATCH);
	barrier ();
	count2 = ioc_readb(IOC_T0CNTL) | (ioc_readb(IOC_T0CNTH) << 8);

	offset = count2;
	if (count2 < count1) {
		/*
		 * We have not had an interrupt between reading count1
		 * and count2.
		 */
		if (status & (1 << 5))
			offset -= RPC_LATCH;
	} else if (count2 > count1) {
		/*
		 * We have just had another interrupt between reading
		 * count1 and count2.
		 */
		offset -= RPC_LATCH;
	}

	offset = (RPC_LATCH - offset) * (tick_nsec / 1000);
	return DIV_ROUND_CLOSEST(offset, RPC_LATCH) * 1000;
}