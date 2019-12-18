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
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCFEV_CLOCK_CONTROL ; 
 int /*<<< orphan*/  DCFEV_CLOCK_ENABLE ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dce_underlay_clock_enable(struct dce_hwseq *hws)
{
	/* todo: why do we need this at boot? is dce_enable_fe_clock enough? */
	if (REG(DCFEV_CLOCK_CONTROL))
		REG_UPDATE(DCFEV_CLOCK_CONTROL,
				DCFEV_CLOCK_ENABLE, 1);
}