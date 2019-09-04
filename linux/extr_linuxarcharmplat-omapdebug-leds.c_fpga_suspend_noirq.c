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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  leds; } ;

/* Variables and functions */
 TYPE_1__* fpga ; 
 int /*<<< orphan*/  fpga_led_state ; 
 int /*<<< orphan*/  readw_relaxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew_relaxed (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fpga_suspend_noirq(struct device *dev)
{
	fpga_led_state = readw_relaxed(&fpga->leds);
	writew_relaxed(0xff, &fpga->leds);

	return 0;
}