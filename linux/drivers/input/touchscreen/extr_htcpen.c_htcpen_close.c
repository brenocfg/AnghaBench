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
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_DISABLE ; 
 int /*<<< orphan*/  HTCPEN_IRQ ; 
 int /*<<< orphan*/  HTCPEN_PORT_INIT ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void htcpen_close(struct input_dev *dev)
{
	outb_p(DEVICE_DISABLE, HTCPEN_PORT_INIT);
	synchronize_irq(HTCPEN_IRQ);
}