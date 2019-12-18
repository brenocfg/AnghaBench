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
struct mce_kbd_dec {int /*<<< orphan*/  rx_timeout; } ;
struct TYPE_2__ {struct mce_kbd_dec mce_kbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ir_mce_kbd_unregister(struct rc_dev *dev)
{
	struct mce_kbd_dec *mce_kbd = &dev->raw->mce_kbd;

	del_timer_sync(&mce_kbd->rx_timeout);

	return 0;
}