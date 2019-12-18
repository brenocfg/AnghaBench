#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct ath10k_hif_ops {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  tx_credits_wq; } ;
struct TYPE_13__ {int /*<<< orphan*/  empty_tx_wq; } ;
struct TYPE_12__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  on_channel; int /*<<< orphan*/  completed; int /*<<< orphan*/  started; } ;
struct TYPE_11__ {int /*<<< orphan*/  wmi_sync; } ;
struct TYPE_10__ {int /*<<< orphan*/  wakeup_completed; } ;
struct TYPE_9__ {int bus; struct ath10k_hif_ops const* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw; struct ath10k* priv; } ;
struct ath10k {int hw_rev; void* workqueue; void* workqueue_aux; int /*<<< orphan*/  napi_dev; int /*<<< orphan*/  set_coverage_class_work; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  register_work; int /*<<< orphan*/  wmi_mgmt_tx_queue; int /*<<< orphan*/  wmi_mgmt_tx_work; int /*<<< orphan*/  offchan_tx_queue; int /*<<< orphan*/  offchan_tx_work; int /*<<< orphan*/  offchan_tx_completed; TYPE_7__ wmi; TYPE_6__ htt; int /*<<< orphan*/  peer_mapping_wq; int /*<<< orphan*/  peers; int /*<<< orphan*/  data_lock; int /*<<< orphan*/  dump_mutex; int /*<<< orphan*/  conf_mutex; TYPE_5__ scan; int /*<<< orphan*/  peer_delete_done; int /*<<< orphan*/  bss_survey_done; TYPE_4__ thermal; int /*<<< orphan*/  vdev_delete_done; int /*<<< orphan*/  vdev_setup_done; int /*<<< orphan*/  install_key_done; TYPE_3__ wow; int /*<<< orphan*/  driver_recovery; int /*<<< orphan*/  target_suspend; int /*<<< orphan*/ * hw_values; int /*<<< orphan*/ * hw_ce_regs; int /*<<< orphan*/ * regs; TYPE_2__ hif; struct device* dev; int /*<<< orphan*/  hw; TYPE_1__ ath_common; } ;
typedef  enum ath10k_hw_rev { ____Placeholder_ath10k_hw_rev } ath10k_hw_rev ;
typedef  enum ath10k_bus { ____Placeholder_ath10k_bus } ath10k_bus ;

/* Variables and functions */
#define  ATH10K_HW_QCA4019 136 
#define  ATH10K_HW_QCA6174 135 
#define  ATH10K_HW_QCA9377 134 
#define  ATH10K_HW_QCA9887 133 
#define  ATH10K_HW_QCA9888 132 
#define  ATH10K_HW_QCA988X 131 
#define  ATH10K_HW_QCA9984 130 
#define  ATH10K_HW_QCA99X0 129 
#define  ATH10K_HW_WCN3990 128 
 int ENOTSUPP ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_core_register_work ; 
 int /*<<< orphan*/  ath10k_core_restart ; 
 int /*<<< orphan*/  ath10k_core_set_coverage_class_work ; 
 int ath10k_coredump_create (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_coredump_destroy (struct ath10k*) ; 
 int ath10k_debug_create (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 struct ath10k* ath10k_mac_create (size_t) ; 
 int /*<<< orphan*/  ath10k_mac_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_mgmt_over_wmi_tx_work ; 
 int /*<<< orphan*/  ath10k_offchan_tx_work ; 
 int /*<<< orphan*/  ath10k_scan_timeout_work ; 
 void* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dummy_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qca4019_regs ; 
 int /*<<< orphan*/  qca4019_values ; 
 int /*<<< orphan*/  qca6174_regs ; 
 int /*<<< orphan*/  qca6174_values ; 
 int /*<<< orphan*/  qca9888_values ; 
 int /*<<< orphan*/  qca988x_regs ; 
 int /*<<< orphan*/  qca988x_values ; 
 int /*<<< orphan*/  qca99x0_regs ; 
 int /*<<< orphan*/  qca99x0_values ; 
 int /*<<< orphan*/  qcax_ce_regs ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn3990_ce_regs ; 
 int /*<<< orphan*/  wcn3990_regs ; 
 int /*<<< orphan*/  wcn3990_values ; 

struct ath10k *ath10k_core_create(size_t priv_size, struct device *dev,
				  enum ath10k_bus bus,
				  enum ath10k_hw_rev hw_rev,
				  const struct ath10k_hif_ops *hif_ops)
{
	struct ath10k *ar;
	int ret;

	ar = ath10k_mac_create(priv_size);
	if (!ar)
		return NULL;

	ar->ath_common.priv = ar;
	ar->ath_common.hw = ar->hw;
	ar->dev = dev;
	ar->hw_rev = hw_rev;
	ar->hif.ops = hif_ops;
	ar->hif.bus = bus;

	switch (hw_rev) {
	case ATH10K_HW_QCA988X:
	case ATH10K_HW_QCA9887:
		ar->regs = &qca988x_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca988x_values;
		break;
	case ATH10K_HW_QCA6174:
	case ATH10K_HW_QCA9377:
		ar->regs = &qca6174_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca6174_values;
		break;
	case ATH10K_HW_QCA99X0:
	case ATH10K_HW_QCA9984:
		ar->regs = &qca99x0_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca99x0_values;
		break;
	case ATH10K_HW_QCA9888:
		ar->regs = &qca99x0_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca9888_values;
		break;
	case ATH10K_HW_QCA4019:
		ar->regs = &qca4019_regs;
		ar->hw_ce_regs = &qcax_ce_regs;
		ar->hw_values = &qca4019_values;
		break;
	case ATH10K_HW_WCN3990:
		ar->regs = &wcn3990_regs;
		ar->hw_ce_regs = &wcn3990_ce_regs;
		ar->hw_values = &wcn3990_values;
		break;
	default:
		ath10k_err(ar, "unsupported core hardware revision %d\n",
			   hw_rev);
		ret = -ENOTSUPP;
		goto err_free_mac;
	}

	init_completion(&ar->scan.started);
	init_completion(&ar->scan.completed);
	init_completion(&ar->scan.on_channel);
	init_completion(&ar->target_suspend);
	init_completion(&ar->driver_recovery);
	init_completion(&ar->wow.wakeup_completed);

	init_completion(&ar->install_key_done);
	init_completion(&ar->vdev_setup_done);
	init_completion(&ar->vdev_delete_done);
	init_completion(&ar->thermal.wmi_sync);
	init_completion(&ar->bss_survey_done);
	init_completion(&ar->peer_delete_done);

	INIT_DELAYED_WORK(&ar->scan.timeout, ath10k_scan_timeout_work);

	ar->workqueue = create_singlethread_workqueue("ath10k_wq");
	if (!ar->workqueue)
		goto err_free_mac;

	ar->workqueue_aux = create_singlethread_workqueue("ath10k_aux_wq");
	if (!ar->workqueue_aux)
		goto err_free_wq;

	mutex_init(&ar->conf_mutex);
	mutex_init(&ar->dump_mutex);
	spin_lock_init(&ar->data_lock);

	INIT_LIST_HEAD(&ar->peers);
	init_waitqueue_head(&ar->peer_mapping_wq);
	init_waitqueue_head(&ar->htt.empty_tx_wq);
	init_waitqueue_head(&ar->wmi.tx_credits_wq);

	init_completion(&ar->offchan_tx_completed);
	INIT_WORK(&ar->offchan_tx_work, ath10k_offchan_tx_work);
	skb_queue_head_init(&ar->offchan_tx_queue);

	INIT_WORK(&ar->wmi_mgmt_tx_work, ath10k_mgmt_over_wmi_tx_work);
	skb_queue_head_init(&ar->wmi_mgmt_tx_queue);

	INIT_WORK(&ar->register_work, ath10k_core_register_work);
	INIT_WORK(&ar->restart_work, ath10k_core_restart);
	INIT_WORK(&ar->set_coverage_class_work,
		  ath10k_core_set_coverage_class_work);

	init_dummy_netdev(&ar->napi_dev);

	ret = ath10k_coredump_create(ar);
	if (ret)
		goto err_free_aux_wq;

	ret = ath10k_debug_create(ar);
	if (ret)
		goto err_free_coredump;

	return ar;

err_free_coredump:
	ath10k_coredump_destroy(ar);

err_free_aux_wq:
	destroy_workqueue(ar->workqueue_aux);
err_free_wq:
	destroy_workqueue(ar->workqueue);

err_free_mac:
	ath10k_mac_destroy(ar);

	return NULL;
}