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
typedef  int u32 ;
struct jme_adapter {int /*<<< orphan*/  rxclean_task; int /*<<< orphan*/  rxempty_task; int /*<<< orphan*/  rx_empty; int /*<<< orphan*/  flags; int /*<<< orphan*/  txclean_task; int /*<<< orphan*/  pcc_task; int /*<<< orphan*/  linkch_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_ENABLE ; 
 int INTR_LINKCH ; 
 int INTR_PCCRX0 ; 
 int INTR_PCCRX0TO ; 
 int INTR_PCCTX ; 
 int INTR_PCCTXTO ; 
 int INTR_RX0 ; 
 int INTR_RX0EMP ; 
 int INTR_SWINTR ; 
 int INTR_TMINTR ; 
 int INTR_TX0 ; 
 int /*<<< orphan*/  JME_FLAG_POLL ; 
 int /*<<< orphan*/  JME_IENC ; 
 int /*<<< orphan*/  JME_IENS ; 
 int /*<<< orphan*/  JME_IEVE ; 
 int /*<<< orphan*/  JME_RX_SCHEDULE (struct jme_adapter*) ; 
 int /*<<< orphan*/  JME_RX_SCHEDULE_PREP (struct jme_adapter*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_polling_mode (struct jme_adapter*) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jwrite32f (struct jme_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_intr_msi(struct jme_adapter *jme, u32 intrstat)
{
	/*
	 * Disable interrupt
	 */
	jwrite32f(jme, JME_IENC, INTR_ENABLE);

	if (intrstat & (INTR_LINKCH | INTR_SWINTR)) {
		/*
		 * Link change event is critical
		 * all other events are ignored
		 */
		jwrite32(jme, JME_IEVE, intrstat);
		tasklet_schedule(&jme->linkch_task);
		goto out_reenable;
	}

	if (intrstat & INTR_TMINTR) {
		jwrite32(jme, JME_IEVE, INTR_TMINTR);
		tasklet_schedule(&jme->pcc_task);
	}

	if (intrstat & (INTR_PCCTXTO | INTR_PCCTX)) {
		jwrite32(jme, JME_IEVE, INTR_PCCTXTO | INTR_PCCTX | INTR_TX0);
		tasklet_schedule(&jme->txclean_task);
	}

	if ((intrstat & (INTR_PCCRX0TO | INTR_PCCRX0 | INTR_RX0EMP))) {
		jwrite32(jme, JME_IEVE, (intrstat & (INTR_PCCRX0TO |
						     INTR_PCCRX0 |
						     INTR_RX0EMP)) |
					INTR_RX0);
	}

	if (test_bit(JME_FLAG_POLL, &jme->flags)) {
		if (intrstat & INTR_RX0EMP)
			atomic_inc(&jme->rx_empty);

		if ((intrstat & (INTR_PCCRX0TO | INTR_PCCRX0 | INTR_RX0EMP))) {
			if (likely(JME_RX_SCHEDULE_PREP(jme))) {
				jme_polling_mode(jme);
				JME_RX_SCHEDULE(jme);
			}
		}
	} else {
		if (intrstat & INTR_RX0EMP) {
			atomic_inc(&jme->rx_empty);
			tasklet_hi_schedule(&jme->rxempty_task);
		} else if (intrstat & (INTR_PCCRX0TO | INTR_PCCRX0)) {
			tasklet_hi_schedule(&jme->rxclean_task);
		}
	}

out_reenable:
	/*
	 * Re-enable interrupt
	 */
	jwrite32f(jme, JME_IENS, INTR_ENABLE);
}