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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int valid_functions; int txq_first_id; int rxq_first_id; int msix_vector_first_id; int max_mtu; int num_rxq; int num_txq; int num_msix_vectors; } ;
struct ice_hw_func_caps {int guar_num_vsi; TYPE_1__ common_cap; } ;
struct ice_hw_dev_caps {int guar_num_vsi; TYPE_1__ common_cap; } ;
struct ice_hw {struct ice_hw_func_caps dev_caps; struct ice_hw_func_caps func_caps; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 scalar_t__ ICE_MAX_FUNCS ; 
 int /*<<< orphan*/  memset (struct ice_hw_func_caps*,int /*<<< orphan*/ ,int) ; 

void ice_set_safe_mode_caps(struct ice_hw *hw)
{
	struct ice_hw_func_caps *func_caps = &hw->func_caps;
	struct ice_hw_dev_caps *dev_caps = &hw->dev_caps;
	u32 valid_func, rxq_first_id, txq_first_id;
	u32 msix_vector_first_id, max_mtu;
	u32 num_func = 0;
	u8 i;

	/* cache some func_caps values that should be restored after memset */
	valid_func = func_caps->common_cap.valid_functions;
	txq_first_id = func_caps->common_cap.txq_first_id;
	rxq_first_id = func_caps->common_cap.rxq_first_id;
	msix_vector_first_id = func_caps->common_cap.msix_vector_first_id;
	max_mtu = func_caps->common_cap.max_mtu;

	/* unset func capabilities */
	memset(func_caps, 0, sizeof(*func_caps));

	/* restore cached values */
	func_caps->common_cap.valid_functions = valid_func;
	func_caps->common_cap.txq_first_id = txq_first_id;
	func_caps->common_cap.rxq_first_id = rxq_first_id;
	func_caps->common_cap.msix_vector_first_id = msix_vector_first_id;
	func_caps->common_cap.max_mtu = max_mtu;

	/* one Tx and one Rx queue in safe mode */
	func_caps->common_cap.num_rxq = 1;
	func_caps->common_cap.num_txq = 1;

	/* two MSIX vectors, one for traffic and one for misc causes */
	func_caps->common_cap.num_msix_vectors = 2;
	func_caps->guar_num_vsi = 1;

	/* cache some dev_caps values that should be restored after memset */
	valid_func = dev_caps->common_cap.valid_functions;
	txq_first_id = dev_caps->common_cap.txq_first_id;
	rxq_first_id = dev_caps->common_cap.rxq_first_id;
	msix_vector_first_id = dev_caps->common_cap.msix_vector_first_id;
	max_mtu = dev_caps->common_cap.max_mtu;

	/* unset dev capabilities */
	memset(dev_caps, 0, sizeof(*dev_caps));

	/* restore cached values */
	dev_caps->common_cap.valid_functions = valid_func;
	dev_caps->common_cap.txq_first_id = txq_first_id;
	dev_caps->common_cap.rxq_first_id = rxq_first_id;
	dev_caps->common_cap.msix_vector_first_id = msix_vector_first_id;
	dev_caps->common_cap.max_mtu = max_mtu;

	/* valid_func is a bitmap. get number of functions */
#define ICE_MAX_FUNCS 8
	for (i = 0; i < ICE_MAX_FUNCS; i++)
		if (valid_func & BIT(i))
			num_func++;

	/* one Tx and one Rx queue per function in safe mode */
	dev_caps->common_cap.num_rxq = num_func;
	dev_caps->common_cap.num_txq = num_func;

	/* two MSIX vectors per function */
	dev_caps->common_cap.num_msix_vectors = 2 * num_func;
}