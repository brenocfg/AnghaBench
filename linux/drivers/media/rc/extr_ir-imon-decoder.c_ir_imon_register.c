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
struct rc_dev {TYPE_1__* raw; } ;
struct imon_dec {int stick_keyboard; } ;
struct TYPE_2__ {struct imon_dec imon; } ;

/* Variables and functions */

__attribute__((used)) static int ir_imon_register(struct rc_dev *dev)
{
	struct imon_dec *imon = &dev->raw->imon;

	imon->stick_keyboard = false;

	return 0;
}