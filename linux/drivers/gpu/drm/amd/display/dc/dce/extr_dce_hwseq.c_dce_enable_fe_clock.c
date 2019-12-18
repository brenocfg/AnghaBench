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
 int /*<<< orphan*/ * DCFE_CLOCK_CONTROL ; 
 int /*<<< orphan*/  DCFE_CLOCK_ENABLE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void dce_enable_fe_clock(struct dce_hwseq *hws,
		unsigned int fe_inst, bool enable)
{
	REG_UPDATE(DCFE_CLOCK_CONTROL[fe_inst],
			DCFE_CLOCK_ENABLE, enable);
}