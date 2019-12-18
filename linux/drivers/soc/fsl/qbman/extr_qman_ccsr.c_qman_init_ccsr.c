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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_EIRQ_PEBI ; 
 int /*<<< orphan*/  REG_ERR_ISR ; 
 int /*<<< orphan*/  fqd_a ; 
 int fqd_sz ; 
 int /*<<< orphan*/  pfdr_a ; 
 int pfdr_sz ; 
 int /*<<< orphan*/  qm_ccsr_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_dc_portal_fman0 ; 
 int /*<<< orphan*/  qm_dc_portal_fman1 ; 
 int qm_init_pfdr (struct device*,int,int) ; 
 int /*<<< orphan*/  qm_memory_fqd ; 
 int /*<<< orphan*/  qm_memory_pfdr ; 
 int /*<<< orphan*/  qm_set_corenet_initiator () ; 
 int /*<<< orphan*/  qm_set_dc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_set_hid () ; 
 int qm_set_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qm_set_pfdr_threshold (int,int) ; 
 int /*<<< orphan*/  qm_set_sfdr_threshold (int) ; 
 int /*<<< orphan*/  qm_set_wq_scheduling (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qm_wq_first ; 
 int qm_wq_last ; 

__attribute__((used)) static int qman_init_ccsr(struct device *dev)
{
	int i, err;

	/* FQD memory */
	err = qm_set_memory(qm_memory_fqd, fqd_a, fqd_sz);
	if (err < 0)
		return err;
	/* PFDR memory */
	err = qm_set_memory(qm_memory_pfdr, pfdr_a, pfdr_sz);
	if (err < 0)
		return err;
	/* Only initialize PFDRs if the QMan was not initialized before */
	if (err == 0) {
		err = qm_init_pfdr(dev, 8, pfdr_sz / 64 - 8);
		if (err)
			return err;
	}
	/* thresholds */
	qm_set_pfdr_threshold(512, 64);
	qm_set_sfdr_threshold(128);
	/* clear stale PEBI bit from interrupt status register */
	qm_ccsr_out(REG_ERR_ISR, QM_EIRQ_PEBI);
	/* corenet initiator settings */
	qm_set_corenet_initiator();
	/* HID settings */
	qm_set_hid();
	/* Set scheduling weights to defaults */
	for (i = qm_wq_first; i <= qm_wq_last; i++)
		qm_set_wq_scheduling(i, 0, 0, 0, 0, 0, 0, 0);
	/* We are not prepared to accept ERNs for hardware enqueues */
	qm_set_dc(qm_dc_portal_fman0, 1, 0);
	qm_set_dc(qm_dc_portal_fman1, 1, 0);
	return 0;
}