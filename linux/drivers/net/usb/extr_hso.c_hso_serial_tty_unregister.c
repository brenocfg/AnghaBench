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
struct hso_serial {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_drv ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hso_serial_tty_unregister(struct hso_serial *serial)
{
	tty_unregister_device(tty_drv, serial->minor);
}