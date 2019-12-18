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
struct dvb_ca_slot {int slot_state; int /*<<< orphan*/  da_irq_supported; } ;
struct dvb_ca_private {int slot_count; int flags; int delay; int /*<<< orphan*/  open; struct dvb_ca_slot* slot_info; } ;

/* Variables and functions */
 int DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE ; 
 int DVB_CA_EN50221_FLAG_IRQ_DA ; 
#define  DVB_CA_SLOTSTATE_INVALID 135 
#define  DVB_CA_SLOTSTATE_LINKINIT 134 
#define  DVB_CA_SLOTSTATE_NONE 133 
#define  DVB_CA_SLOTSTATE_RUNNING 132 
#define  DVB_CA_SLOTSTATE_UNINITIALISED 131 
#define  DVB_CA_SLOTSTATE_VALIDATE 130 
#define  DVB_CA_SLOTSTATE_WAITFR 129 
#define  DVB_CA_SLOTSTATE_WAITREADY 128 
 int HZ ; 

__attribute__((used)) static void dvb_ca_en50221_thread_update_delay(struct dvb_ca_private *ca)
{
	int delay;
	int curdelay = 100000000;
	int slot;

	/*
	 * Beware of too high polling frequency, because one polling
	 * call might take several hundred milliseconds until timeout!
	 */
	for (slot = 0; slot < ca->slot_count; slot++) {
		struct dvb_ca_slot *sl = &ca->slot_info[slot];

		switch (sl->slot_state) {
		default:
		case DVB_CA_SLOTSTATE_NONE:
			delay = HZ * 60;  /* 60s */
			if (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE))
				delay = HZ * 5;  /* 5s */
			break;
		case DVB_CA_SLOTSTATE_INVALID:
			delay = HZ * 60;  /* 60s */
			if (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE))
				delay = HZ / 10;  /* 100ms */
			break;

		case DVB_CA_SLOTSTATE_UNINITIALISED:
		case DVB_CA_SLOTSTATE_WAITREADY:
		case DVB_CA_SLOTSTATE_VALIDATE:
		case DVB_CA_SLOTSTATE_WAITFR:
		case DVB_CA_SLOTSTATE_LINKINIT:
			delay = HZ / 10;  /* 100ms */
			break;

		case DVB_CA_SLOTSTATE_RUNNING:
			delay = HZ * 60;  /* 60s */
			if (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE))
				delay = HZ / 10;  /* 100ms */
			if (ca->open) {
				if ((!sl->da_irq_supported) ||
				    (!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_DA)))
					delay = HZ / 10;  /* 100ms */
			}
			break;
		}

		if (delay < curdelay)
			curdelay = delay;
	}

	ca->delay = curdelay;
}