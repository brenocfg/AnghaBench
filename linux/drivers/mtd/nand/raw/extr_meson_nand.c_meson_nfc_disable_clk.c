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
struct meson_nfc {int /*<<< orphan*/  core_clk; int /*<<< orphan*/  device_clk; int /*<<< orphan*/  phase_tx; int /*<<< orphan*/  phase_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_nfc_disable_clk(struct meson_nfc *nfc)
{
	clk_disable_unprepare(nfc->phase_rx);
	clk_disable_unprepare(nfc->phase_tx);
	clk_disable_unprepare(nfc->device_clk);
	clk_disable_unprepare(nfc->core_clk);
}