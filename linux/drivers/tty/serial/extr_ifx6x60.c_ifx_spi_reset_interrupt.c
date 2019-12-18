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
struct TYPE_2__ {int /*<<< orphan*/  reset_out; } ;
struct ifx_spi_device {int /*<<< orphan*/  mdm_reset_wait; int /*<<< orphan*/  mdm_reset_state; int /*<<< orphan*/  tty_port; TYPE_1__ gpio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MR_COMPLETE ; 
 int /*<<< orphan*/  MR_INPROGRESS ; 
 int /*<<< orphan*/  MR_START ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ifx_spi_reset_interrupt(int irq, void *dev)
{
	struct ifx_spi_device *ifx_dev = dev;
	int val = gpio_get_value(ifx_dev->gpio.reset_out);
	int solreset = test_bit(MR_START, &ifx_dev->mdm_reset_state);

	if (val == 0) {
		/* entered reset */
		set_bit(MR_INPROGRESS, &ifx_dev->mdm_reset_state);
		if (!solreset) {
			/* unsolicited reset  */
			tty_port_tty_hangup(&ifx_dev->tty_port, false);
		}
	} else {
		/* exited reset */
		clear_bit(MR_INPROGRESS, &ifx_dev->mdm_reset_state);
		if (solreset) {
			set_bit(MR_COMPLETE, &ifx_dev->mdm_reset_state);
			wake_up(&ifx_dev->mdm_reset_wait);
		}
	}
	return IRQ_HANDLED;
}