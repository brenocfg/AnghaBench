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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ cmd_off; } ;
struct TYPE_4__ {TYPE_1__ cmd; int /*<<< orphan*/  fanreg; } ;

/* Variables and functions */
 int ACERHDF_FAN_AUTO ; 
 int ACERHDF_FAN_OFF ; 
 int EINVAL ; 
 TYPE_2__ ctrl_cfg ; 
 scalar_t__ ec_read (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int acerhdf_get_fanstate(int *state)
{
	u8 fan;

	if (ec_read(ctrl_cfg.fanreg, &fan))
		return -EINVAL;

	if (fan != ctrl_cfg.cmd.cmd_off)
		*state = ACERHDF_FAN_AUTO;
	else
		*state = ACERHDF_FAN_OFF;

	return 0;
}