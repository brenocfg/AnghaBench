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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct tc_cls_u32_offload {TYPE_1__ hnode; } ;
struct ixgbe_adapter {int /*<<< orphan*/  tables; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IXGBE_MAX_LINK_HANDLE ; 
 scalar_t__ TC_U32_USERHTID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_configure_clsu32_del_hnode(struct ixgbe_adapter *adapter,
					    struct tc_cls_u32_offload *cls)
{
	u32 uhtid = TC_U32_USERHTID(cls->hnode.handle);

	if (uhtid >= IXGBE_MAX_LINK_HANDLE)
		return -EINVAL;

	clear_bit(uhtid - 1, &adapter->tables);
	return 0;
}