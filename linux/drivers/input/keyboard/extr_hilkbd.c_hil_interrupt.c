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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned char s; unsigned char c; int valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  handle_data (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  handle_status (unsigned char,unsigned char) ; 
 TYPE_1__ hil_dev ; 
 unsigned char hil_read_data () ; 
 unsigned char hil_status () ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static irqreturn_t hil_interrupt(int irq, void *handle)
{
	unsigned char s, c;

	s = hil_status();
	c = hil_read_data();

	switch (s >> 4) {
	case 0x5:
		handle_status(s, c);
		break;
	case 0x6:
		handle_data(s, c);
		break;
	case 0x4:
		hil_dev.s = s;
		hil_dev.c = c;
		mb();
		hil_dev.valid = 1;
		break;
	}
	return IRQ_HANDLED;
}