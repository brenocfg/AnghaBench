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
struct ath10k_snoc {struct ath10k_qmi* qmi; } ;
struct ath10k_qmi {int /*<<< orphan*/  event_wq; int /*<<< orphan*/  event_work; int /*<<< orphan*/  qmi_hdl; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ath10k_qmi*) ; 
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 

int ath10k_qmi_deinit(struct ath10k *ar)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_qmi *qmi = ar_snoc->qmi;

	qmi_handle_release(&qmi->qmi_hdl);
	cancel_work_sync(&qmi->event_work);
	destroy_workqueue(qmi->event_wq);
	kfree(qmi);
	ar_snoc->qmi = NULL;

	return 0;
}