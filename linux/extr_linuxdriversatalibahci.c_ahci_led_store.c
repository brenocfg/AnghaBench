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
struct ata_port {TYPE_1__* ops; struct ahci_port_priv* private_data; } ;
struct ahci_port_priv {struct ahci_em_priv* em_priv; } ;
struct ahci_em_priv {scalar_t__ blink_policy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* transmit_led_message ) (struct ata_port*,unsigned int,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int EM_MAX_SLOTS ; 
 unsigned int EM_MSG_LED_PMP_SLOT ; 
 unsigned int EM_MSG_LED_VALUE_ACTIVITY ; 
 int array_index_nospec (int,int) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,unsigned int,size_t) ; 

__attribute__((used)) static ssize_t ahci_led_store(struct ata_port *ap, const char *buf,
				size_t size)
{
	unsigned int state;
	int pmp;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_em_priv *emp;

	if (kstrtouint(buf, 0, &state) < 0)
		return -EINVAL;

	/* get the slot number from the message */
	pmp = (state & EM_MSG_LED_PMP_SLOT) >> 8;
	if (pmp < EM_MAX_SLOTS) {
		pmp = array_index_nospec(pmp, EM_MAX_SLOTS);
		emp = &pp->em_priv[pmp];
	} else {
		return -EINVAL;
	}

	/* mask off the activity bits if we are in sw_activity
	 * mode, user should turn off sw_activity before setting
	 * activity led through em_message
	 */
	if (emp->blink_policy)
		state &= ~EM_MSG_LED_VALUE_ACTIVITY;

	return ap->ops->transmit_led_message(ap, state, size);
}