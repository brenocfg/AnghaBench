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
struct exynos_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSIM_FIFOCTRL_REG ; 
 int DSIM_SFR_HEADER_FULL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int exynos_dsi_read (struct exynos_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int exynos_dsi_wait_for_hdr_fifo(struct exynos_dsi *dsi)
{
	int timeout = 2000;

	do {
		u32 reg = exynos_dsi_read(dsi, DSIM_FIFOCTRL_REG);

		if (!(reg & DSIM_SFR_HEADER_FULL))
			return 0;

		if (!cond_resched())
			usleep_range(950, 1050);
	} while (--timeout);

	return -ETIMEDOUT;
}