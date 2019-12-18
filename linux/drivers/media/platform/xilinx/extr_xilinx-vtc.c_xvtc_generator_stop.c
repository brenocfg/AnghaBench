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
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;
struct xvtc_device {TYPE_1__ xvip; int /*<<< orphan*/  has_generator; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  XVIP_CTRL_CONTROL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xvip_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int xvtc_generator_stop(struct xvtc_device *xvtc)
{
	if (!xvtc->has_generator)
		return -ENXIO;

	xvip_write(&xvtc->xvip, XVIP_CTRL_CONTROL, 0);

	clk_disable_unprepare(xvtc->xvip.clk);

	return 0;
}