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
struct smi_info {int /*<<< orphan*/  si_state; } ;
struct ipmi_smi_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI_NORMAL ; 
 int /*<<< orphan*/  disable_si_irq (struct smi_info*) ; 
 scalar_t__ enable_si_irq (struct smi_info*) ; 
 struct ipmi_smi_msg* ipmi_alloc_smi_msg () ; 
 int /*<<< orphan*/  ipmi_free_smi_msg (struct ipmi_smi_msg*) ; 

__attribute__((used)) static struct ipmi_smi_msg *alloc_msg_handle_irq(struct smi_info *smi_info)
{
	struct ipmi_smi_msg *msg;

	msg = ipmi_alloc_smi_msg();
	if (!msg) {
		if (!disable_si_irq(smi_info))
			smi_info->si_state = SI_NORMAL;
	} else if (enable_si_irq(smi_info)) {
		ipmi_free_smi_msg(msg);
		msg = NULL;
	}
	return msg;
}