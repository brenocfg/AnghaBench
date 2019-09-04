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

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON_NOT_POWER_OF_2 (int) ; 
 unsigned int IEEE_8021QAZ_MAX_TCS ; 
 int XGMAC_FIFO_MIN_ALLOC ; 
 int XGMAC_FIFO_UNIT ; 

__attribute__((used)) static unsigned int xgbe_set_nonprio_fifos(unsigned int fifo_size,
					   unsigned int queue_count,
					   unsigned int *fifo)
{
	unsigned int i;

	BUILD_BUG_ON_NOT_POWER_OF_2(XGMAC_FIFO_MIN_ALLOC);

	if (queue_count <= IEEE_8021QAZ_MAX_TCS)
		return fifo_size;

	/* Rx queues 9 and up are for specialized packets,
	 * such as PTP or DCB control packets, etc. and
	 * don't require a large fifo
	 */
	for (i = IEEE_8021QAZ_MAX_TCS; i < queue_count; i++) {
		fifo[i] = (XGMAC_FIFO_MIN_ALLOC / XGMAC_FIFO_UNIT) - 1;
		fifo_size -= XGMAC_FIFO_MIN_ALLOC;
	}

	return fifo_size;
}