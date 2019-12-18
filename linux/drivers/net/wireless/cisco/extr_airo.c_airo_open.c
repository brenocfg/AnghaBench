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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; struct airo_info* ml_priv; } ;
struct airo_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  airo_thread_task; int /*<<< orphan*/  jobs; struct net_device* wifidev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FLAG_COMMIT ; 
 int /*<<< orphan*/  FLAG_FLASHING ; 
 int /*<<< orphan*/  FLAG_RADIO_DOWN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB_DIE ; 
 scalar_t__ PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  airo_interrupt ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  airo_thread ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  enable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  enable_interrupts (struct airo_info*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_auto_wep (struct airo_info*) ; 
 int /*<<< orphan*/  writeConfigRid (struct airo_info*,int) ; 

__attribute__((used)) static int airo_open(struct net_device *dev) {
	struct airo_info *ai = dev->ml_priv;
	int rc = 0;

	if (test_bit(FLAG_FLASHING, &ai->flags))
		return -EIO;

	/* Make sure the card is configured.
	 * Wireless Extensions may postpone config changes until the card
	 * is open (to pipeline changes and speed-up card setup). If
	 * those changes are not yet committed, do it now - Jean II */
	if (test_bit(FLAG_COMMIT, &ai->flags)) {
		disable_MAC(ai, 1);
		writeConfigRid(ai, 1);
	}

	if (ai->wifidev != dev) {
		clear_bit(JOB_DIE, &ai->jobs);
		ai->airo_thread_task = kthread_run(airo_thread, dev, "%s",
						   dev->name);
		if (IS_ERR(ai->airo_thread_task))
			return (int)PTR_ERR(ai->airo_thread_task);

		rc = request_irq(dev->irq, airo_interrupt, IRQF_SHARED,
			dev->name, dev);
		if (rc) {
			airo_print_err(dev->name,
				"register interrupt %d failed, rc %d",
				dev->irq, rc);
			set_bit(JOB_DIE, &ai->jobs);
			kthread_stop(ai->airo_thread_task);
			return rc;
		}

		/* Power on the MAC controller (which may have been disabled) */
		clear_bit(FLAG_RADIO_DOWN, &ai->flags);
		enable_interrupts(ai);

		try_auto_wep(ai);
	}
	enable_MAC(ai, 1);

	netif_start_queue(dev);
	return 0;
}