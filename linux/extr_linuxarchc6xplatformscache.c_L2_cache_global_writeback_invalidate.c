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
 int /*<<< orphan*/  IMCR_L2WBINV ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ imcr_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imcr_set (int /*<<< orphan*/ ,int) ; 

void L2_cache_global_writeback_invalidate(void)
{
	imcr_set(IMCR_L2WBINV, 1);
	while (imcr_get(IMCR_L2WBINV))
		cpu_relax();
}