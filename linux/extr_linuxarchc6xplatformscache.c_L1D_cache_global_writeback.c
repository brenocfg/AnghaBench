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
 int /*<<< orphan*/  IMCR_L1DWB ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int imcr_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imcr_set (int /*<<< orphan*/ ,unsigned int) ; 

void L1D_cache_global_writeback(void)
{
	unsigned int set = 1;
	imcr_set(IMCR_L1DWB, set);
	while (imcr_get(IMCR_L1DWB) & 1)
		cpu_relax();
}