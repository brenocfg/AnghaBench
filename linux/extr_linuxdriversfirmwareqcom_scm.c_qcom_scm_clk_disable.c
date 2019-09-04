#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bus_clk; int /*<<< orphan*/  iface_clk; int /*<<< orphan*/  core_clk; } ;

/* Variables and functions */
 TYPE_1__* __scm ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_scm_clk_disable(void)
{
	clk_disable_unprepare(__scm->core_clk);
	clk_disable_unprepare(__scm->iface_clk);
	clk_disable_unprepare(__scm->bus_clk);
}