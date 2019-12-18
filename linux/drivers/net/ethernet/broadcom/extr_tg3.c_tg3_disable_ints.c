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
struct tg3 {int misc_host_ctrl; int irq_max; TYPE_1__* napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_mbox; } ;

/* Variables and functions */
 int MISC_HOST_CTRL_MASK_PCI_INT ; 
 int /*<<< orphan*/  TG3PCI_MISC_HOST_CTRL ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_mailbox_f (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_disable_ints(struct tg3 *tp)
{
	int i;

	tw32(TG3PCI_MISC_HOST_CTRL,
	     (tp->misc_host_ctrl | MISC_HOST_CTRL_MASK_PCI_INT));
	for (i = 0; i < tp->irq_max; i++)
		tw32_mailbox_f(tp->napi[i].int_mbox, 0x00000001);
}