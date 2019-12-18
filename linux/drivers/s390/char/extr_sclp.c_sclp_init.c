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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXT_IRQ_SERVICE_SIG ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQ_SUBCLASS_SERVICE_SIGNAL ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  irq_subclass_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int register_external_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_reboot_notifier (int /*<<< orphan*/ *) ; 
 int sclp_check_interface () ; 
 int /*<<< orphan*/  sclp_init_mask (int) ; 
 void* sclp_init_sccb ; 
 scalar_t__ sclp_init_state ; 
 scalar_t__ sclp_init_state_initialized ; 
 scalar_t__ sclp_init_state_initializing ; 
 scalar_t__ sclp_init_state_uninitialized ; 
 int /*<<< orphan*/  sclp_interrupt_handler ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_queue_timer ; 
 void* sclp_read_sccb ; 
 int /*<<< orphan*/  sclp_reboot_notifier ; 
 int /*<<< orphan*/  sclp_reg_list ; 
 int /*<<< orphan*/  sclp_req_queue ; 
 int /*<<< orphan*/ * sclp_req_queue_timeout ; 
 int /*<<< orphan*/  sclp_request_timer ; 
 TYPE_1__ sclp_state_change_event ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sclp_init(void)
{
	unsigned long flags;
	int rc = 0;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Check for previous or running initialization */
	if (sclp_init_state != sclp_init_state_uninitialized)
		goto fail_unlock;
	sclp_init_state = sclp_init_state_initializing;
	sclp_read_sccb = (void *) __get_free_page(GFP_ATOMIC | GFP_DMA);
	sclp_init_sccb = (void *) __get_free_page(GFP_ATOMIC | GFP_DMA);
	BUG_ON(!sclp_read_sccb || !sclp_init_sccb);
	/* Set up variables */
	INIT_LIST_HEAD(&sclp_req_queue);
	INIT_LIST_HEAD(&sclp_reg_list);
	list_add(&sclp_state_change_event.list, &sclp_reg_list);
	timer_setup(&sclp_request_timer, NULL, 0);
	timer_setup(&sclp_queue_timer, sclp_req_queue_timeout, 0);
	/* Check interface */
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_check_interface();
	spin_lock_irqsave(&sclp_lock, flags);
	if (rc)
		goto fail_init_state_uninitialized;
	/* Register reboot handler */
	rc = register_reboot_notifier(&sclp_reboot_notifier);
	if (rc)
		goto fail_init_state_uninitialized;
	/* Register interrupt handler */
	rc = register_external_irq(EXT_IRQ_SERVICE_SIG, sclp_interrupt_handler);
	if (rc)
		goto fail_unregister_reboot_notifier;
	sclp_init_state = sclp_init_state_initialized;
	spin_unlock_irqrestore(&sclp_lock, flags);
	/* Enable service-signal external interruption - needs to happen with
	 * IRQs enabled. */
	irq_subclass_register(IRQ_SUBCLASS_SERVICE_SIGNAL);
	sclp_init_mask(1);
	return 0;

fail_unregister_reboot_notifier:
	unregister_reboot_notifier(&sclp_reboot_notifier);
fail_init_state_uninitialized:
	sclp_init_state = sclp_init_state_uninitialized;
	free_page((unsigned long) sclp_read_sccb);
	free_page((unsigned long) sclp_init_sccb);
fail_unlock:
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}