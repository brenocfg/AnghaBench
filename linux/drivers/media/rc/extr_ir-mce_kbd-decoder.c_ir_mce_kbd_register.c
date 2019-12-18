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
struct mce_kbd_dec {int /*<<< orphan*/  keylock; int /*<<< orphan*/  rx_timeout; } ;
struct TYPE_2__ {struct mce_kbd_dec mce_kbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mce_kbd_rx_timeout ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir_mce_kbd_register(struct rc_dev *dev)
{
	struct mce_kbd_dec *mce_kbd = &dev->raw->mce_kbd;

	timer_setup(&mce_kbd->rx_timeout, mce_kbd_rx_timeout, 0);
	spin_lock_init(&mce_kbd->keylock);

	return 0;
}