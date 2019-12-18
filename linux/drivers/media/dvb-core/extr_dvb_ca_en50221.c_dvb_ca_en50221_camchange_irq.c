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
struct dvb_ca_slot {int camchange_type; int /*<<< orphan*/  camchange_count; } ;
struct dvb_ca_private {struct dvb_ca_slot* slot_info; } ;
struct dvb_ca_en50221 {struct dvb_ca_private* private; } ;

/* Variables and functions */
#define  DVB_CA_EN50221_CAMCHANGE_INSERTED 129 
#define  DVB_CA_EN50221_CAMCHANGE_REMOVED 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int /*<<< orphan*/  dvb_ca_en50221_thread_wakeup (struct dvb_ca_private*) ; 

void dvb_ca_en50221_camchange_irq(struct dvb_ca_en50221 *pubca, int slot,
				  int change_type)
{
	struct dvb_ca_private *ca = pubca->private;
	struct dvb_ca_slot *sl = &ca->slot_info[slot];

	dprintk("CAMCHANGE IRQ slot:%i change_type:%i\n", slot, change_type);

	switch (change_type) {
	case DVB_CA_EN50221_CAMCHANGE_REMOVED:
	case DVB_CA_EN50221_CAMCHANGE_INSERTED:
		break;

	default:
		return;
	}

	sl->camchange_type = change_type;
	atomic_inc(&sl->camchange_count);
	dvb_ca_en50221_thread_wakeup(ca);
}