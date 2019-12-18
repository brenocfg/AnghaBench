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
struct panfrost_device {int /*<<< orphan*/  clock; int /*<<< orphan*/  bus_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panfrost_clk_fini(struct panfrost_device *pfdev)
{
	clk_disable_unprepare(pfdev->bus_clock);
	clk_disable_unprepare(pfdev->clock);
}