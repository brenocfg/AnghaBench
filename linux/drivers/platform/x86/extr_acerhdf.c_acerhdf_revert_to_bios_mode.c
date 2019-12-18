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
struct TYPE_2__ {scalar_t__ polling_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACERHDF_FAN_AUTO ; 
 int /*<<< orphan*/  acerhdf_change_fanstate (int /*<<< orphan*/ ) ; 
 scalar_t__ kernelmode ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 TYPE_1__* thz_dev ; 

__attribute__((used)) static inline void acerhdf_revert_to_bios_mode(void)
{
	acerhdf_change_fanstate(ACERHDF_FAN_AUTO);
	kernelmode = 0;
	if (thz_dev)
		thz_dev->polling_delay = 0;
	pr_notice("kernel mode fan control OFF\n");
}