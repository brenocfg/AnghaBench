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
struct tty_struct {struct ser_device* disc_data; } ;
struct ser_device {struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  handle_tx (struct ser_device*) ; 

__attribute__((used)) static void ldisc_tx_wakeup(struct tty_struct *tty)
{
	struct ser_device *ser;

	ser = tty->disc_data;
	BUG_ON(ser == NULL);
	WARN_ON(ser->tty != tty);
	handle_tx(ser);
}