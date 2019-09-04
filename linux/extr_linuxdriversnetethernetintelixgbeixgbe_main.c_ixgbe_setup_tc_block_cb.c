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
struct ixgbe_adapter {int /*<<< orphan*/  netdev; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSU32 128 
 int ixgbe_setup_tc_cls_u32 (struct ixgbe_adapter*,void*) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int ixgbe_setup_tc_block_cb(enum tc_setup_type type, void *type_data,
				   void *cb_priv)
{
	struct ixgbe_adapter *adapter = cb_priv;

	if (!tc_cls_can_offload_and_chain0(adapter->netdev, type_data))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSU32:
		return ixgbe_setup_tc_cls_u32(adapter, type_data);
	default:
		return -EOPNOTSUPP;
	}
}