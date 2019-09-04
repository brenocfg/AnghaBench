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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  power9_idle_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* stop_psscr_table ; 

__attribute__((used)) static int stop_loop(struct cpuidle_device *dev,
		     struct cpuidle_driver *drv,
		     int index)
{
	power9_idle_type(stop_psscr_table[index].val,
			 stop_psscr_table[index].mask);
	return index;
}