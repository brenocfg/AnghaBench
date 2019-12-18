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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  soc_version; } ;
struct ath10k_snoc {int /*<<< orphan*/  flags; TYPE_1__ target_info; } ;
struct ath10k_bus_params {int /*<<< orphan*/  chip_id; int /*<<< orphan*/  dev_type; } ;
struct ath10k {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DEV_TYPE_LL ; 
 int /*<<< orphan*/  ATH10K_FLAG_CRASH_FLUSH ; 
#define  ATH10K_QMI_EVENT_FW_DOWN_IND 129 
#define  ATH10K_QMI_EVENT_FW_READY_IND 128 
 int /*<<< orphan*/  ATH10K_SNOC_FLAG_RECOVERY ; 
 int /*<<< orphan*/  ATH10K_SNOC_FLAG_REGISTERED ; 
 int /*<<< orphan*/  ATH10K_SNOC_FLAG_UNREGISTERING ; 
 int EINVAL ; 
 int ath10k_core_register (struct ath10k*,struct ath10k_bus_params*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ath10k_snoc_fw_indication(struct ath10k *ar, u64 type)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_bus_params bus_params = {};
	int ret;

	if (test_bit(ATH10K_SNOC_FLAG_UNREGISTERING, &ar_snoc->flags))
		return 0;

	switch (type) {
	case ATH10K_QMI_EVENT_FW_READY_IND:
		if (test_bit(ATH10K_SNOC_FLAG_REGISTERED, &ar_snoc->flags)) {
			queue_work(ar->workqueue, &ar->restart_work);
			break;
		}

		bus_params.dev_type = ATH10K_DEV_TYPE_LL;
		bus_params.chip_id = ar_snoc->target_info.soc_version;
		ret = ath10k_core_register(ar, &bus_params);
		if (ret) {
			ath10k_err(ar, "Failed to register driver core: %d\n",
				   ret);
			return ret;
		}
		set_bit(ATH10K_SNOC_FLAG_REGISTERED, &ar_snoc->flags);
		break;
	case ATH10K_QMI_EVENT_FW_DOWN_IND:
		set_bit(ATH10K_SNOC_FLAG_RECOVERY, &ar_snoc->flags);
		set_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags);
		break;
	default:
		ath10k_err(ar, "invalid fw indication: %llx\n", type);
		return -EINVAL;
	}

	return 0;
}