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
struct inno_hdmi_phy {int /*<<< orphan*/  sysclk; int /*<<< orphan*/  refpclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inno_hdmi_phy_action(void *data)
{
	struct inno_hdmi_phy *inno = data;

	clk_disable_unprepare(inno->refpclk);
	clk_disable_unprepare(inno->sysclk);
}