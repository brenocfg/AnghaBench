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
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MCDE_MAX_WIDTH ; 

__attribute__((used)) static int mcde_dsi_get_pkt_div(int ppl, int fifo_size)
{
	/*
	 * DSI command mode line packets should be split into an even number of
	 * packets smaller than or equal to the fifo size.
	 */
	int div;
	const int max_div = DIV_ROUND_UP(MCDE_MAX_WIDTH, fifo_size);

	for (div = 1; div < max_div; div++)
		if (ppl % div == 0 && ppl / div <= fifo_size)
			return div;
	return 1;
}