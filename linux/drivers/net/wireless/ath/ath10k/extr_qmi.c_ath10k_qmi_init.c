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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_snoc {struct ath10k_qmi* qmi; } ;
struct ath10k_qmi {int /*<<< orphan*/  qmi_hdl; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  event_work; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN ; 
 int /*<<< orphan*/  WLFW_SERVICE_ID_V01 ; 
 int /*<<< orphan*/  WLFW_SERVICE_VERS_V01 ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*) ; 
 int /*<<< orphan*/  ath10k_qmi_driver_event_work ; 
 int /*<<< orphan*/  ath10k_qmi_ops ; 
 int ath10k_qmi_setup_msa_resources (struct ath10k_qmi*,int /*<<< orphan*/ ) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ath10k_qmi*) ; 
 struct ath10k_qmi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qmi_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qmi_handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_msg_handler ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ath10k_qmi_init(struct ath10k *ar, u32 msa_size)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_qmi *qmi;
	int ret;

	qmi = kzalloc(sizeof(*qmi), GFP_KERNEL);
	if (!qmi)
		return -ENOMEM;

	qmi->ar = ar;
	ar_snoc->qmi = qmi;

	ret = ath10k_qmi_setup_msa_resources(qmi, msa_size);
	if (ret)
		goto err;

	ret = qmi_handle_init(&qmi->qmi_hdl,
			      WLFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_MSG_LEN,
			      &ath10k_qmi_ops, qmi_msg_handler);
	if (ret)
		goto err;

	qmi->event_wq = alloc_workqueue("ath10k_qmi_driver_event",
					WQ_UNBOUND, 1);
	if (!qmi->event_wq) {
		ath10k_err(ar, "failed to allocate workqueue\n");
		ret = -EFAULT;
		goto err_release_qmi_handle;
	}

	INIT_LIST_HEAD(&qmi->event_list);
	spin_lock_init(&qmi->event_lock);
	INIT_WORK(&qmi->event_work, ath10k_qmi_driver_event_work);

	ret = qmi_add_lookup(&qmi->qmi_hdl, WLFW_SERVICE_ID_V01,
			     WLFW_SERVICE_VERS_V01, 0);
	if (ret)
		goto err_qmi_lookup;

	return 0;

err_qmi_lookup:
	destroy_workqueue(qmi->event_wq);

err_release_qmi_handle:
	qmi_handle_release(&qmi->qmi_hdl);

err:
	kfree(qmi);
	return ret;
}