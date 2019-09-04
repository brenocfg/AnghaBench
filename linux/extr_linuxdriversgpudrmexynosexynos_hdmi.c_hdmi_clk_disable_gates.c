#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hdmi_context {int /*<<< orphan*/ * clk_gates; TYPE_2__* drv_data; } ;
struct TYPE_3__ {int count; } ;
struct TYPE_4__ {TYPE_1__ clk_gates; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_clk_disable_gates(struct hdmi_context *hdata)
{
	int i = hdata->drv_data->clk_gates.count;

	while (i--)
		clk_disable_unprepare(hdata->clk_gates[i]);
}