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
struct TYPE_3__ {int /*<<< orphan*/  tty; } ;
struct serial_state {TYPE_1__ tport; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int serdatr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SDR_TBE ; 
 TYPE_2__ custom ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  transmit_chars (struct serial_state*) ; 

__attribute__((used)) static irqreturn_t ser_tx_int(int irq, void *dev_id)
{
	struct serial_state *info = dev_id;

	if (custom.serdatr & SDR_TBE) {
#ifdef SERIAL_DEBUG_INTR
	  printk("ser_tx_int...");
#endif

	  if (!info->tport.tty)
		return IRQ_NONE;

	  transmit_chars(info);
#ifdef SERIAL_DEBUG_INTR
	  printk("end.\n");
#endif
	}
	return IRQ_HANDLED;
}