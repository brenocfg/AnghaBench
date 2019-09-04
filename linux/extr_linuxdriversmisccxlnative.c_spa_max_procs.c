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

__attribute__((used)) static int spa_max_procs(int spa_size)
{
	/*
	 * From the CAIA:
	 *    end_of_SPA_area = SPA_Base + ((n+4) * 128) + (( ((n*8) + 127) >> 7) * 128) + 255
	 * Most of that junk is really just an overly-complicated way of saying
	 * the last 256 bytes are __aligned(128), so it's really:
	 *    end_of_SPA_area = end_of_PSL_queue_area + __aligned(128) 255
	 * and
	 *    end_of_PSL_queue_area = SPA_Base + ((n+4) * 128) + (n*8) - 1
	 * so
	 *    sizeof(SPA) = ((n+4) * 128) + (n*8) + __aligned(128) 256
	 * Ignore the alignment (which is safe in this case as long as we are
	 * careful with our rounding) and solve for n:
	 */
	return ((spa_size / 8) - 96) / 17;
}