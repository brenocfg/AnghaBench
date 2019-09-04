#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_dfll {TYPE_3__* soc; int /*<<< orphan*/  tune_range; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_clock_trimmers_low ) () ;TYPE_2__* cvb; } ;
struct TYPE_4__ {int /*<<< orphan*/  tune1; int /*<<< orphan*/  tune0_low; } ;
struct TYPE_5__ {TYPE_1__ cpu_dfll_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_TUNE0 ; 
 int /*<<< orphan*/  DFLL_TUNE1 ; 
 int /*<<< orphan*/  DFLL_TUNE_LOW ; 
 int /*<<< orphan*/  dfll_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void dfll_tune_low(struct tegra_dfll *td)
{
	td->tune_range = DFLL_TUNE_LOW;

	dfll_writel(td, td->soc->cvb->cpu_dfll_data.tune0_low, DFLL_TUNE0);
	dfll_writel(td, td->soc->cvb->cpu_dfll_data.tune1, DFLL_TUNE1);
	dfll_wmb(td);

	if (td->soc->set_clock_trimmers_low)
		td->soc->set_clock_trimmers_low();
}