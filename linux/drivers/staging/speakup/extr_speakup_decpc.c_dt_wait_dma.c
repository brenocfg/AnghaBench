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
 int /*<<< orphan*/  STAT_dma_ready ; 
 int STAT_dma_state ; 
 int dma_state ; 
 int dt_getstatus () ; 
 int /*<<< orphan*/  dt_waitbit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dt_wait_dma(void)
{
	int timeout = 100, state = dma_state;

	if (!dt_waitbit(STAT_dma_ready))
		return 0;
	while (--timeout > 0) {
		if ((dt_getstatus() & STAT_dma_state) == state)
			return 1;
		udelay(50);
	}
	dma_state = dt_getstatus() & STAT_dma_state;
	return 1;
}