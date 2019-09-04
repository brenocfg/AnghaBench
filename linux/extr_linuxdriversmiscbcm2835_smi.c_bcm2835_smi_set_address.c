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
struct bcm2835_smi_instance {int /*<<< orphan*/  transaction_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_set_address (struct bcm2835_smi_instance*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bcm2835_smi_set_address(struct bcm2835_smi_instance *inst,
	unsigned int address)
{
	spin_lock(&inst->transaction_lock);
	smi_set_address(inst, address);
	spin_unlock(&inst->transaction_lock);
}