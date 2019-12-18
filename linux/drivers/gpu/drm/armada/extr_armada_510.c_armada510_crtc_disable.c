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
struct armada_crtc {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void armada510_crtc_disable(struct armada_crtc *dcrtc)
{
	if (dcrtc->clk) {
		clk_disable_unprepare(dcrtc->clk);
		dcrtc->clk = NULL;
	}
}