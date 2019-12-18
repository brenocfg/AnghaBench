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
struct tahvo_usb {int /*<<< orphan*/  serialize; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  check_vbus_state (struct tahvo_usb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tahvo_usb_vbus_interrupt(int irq, void *_tu)
{
	struct tahvo_usb *tu = _tu;

	mutex_lock(&tu->serialize);
	check_vbus_state(tu);
	mutex_unlock(&tu->serialize);

	return IRQ_HANDLED;
}