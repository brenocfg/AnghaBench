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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct igu_ack_register {int sb_id_and_flags; int /*<<< orphan*/  status_block_index; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CNIC_WR (struct cnic_dev*,scalar_t__,scalar_t__) ; 
 scalar_t__ COMMAND_REG_INT_ACK ; 
 scalar_t__ HC_REG_COMMAND_REG ; 
 int IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT ; 
 int IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT ; 
 int IGU_ACK_REGISTER_STORM_ID_SHIFT ; 
 int IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cnic_ack_bnx2x_int(struct cnic_dev *dev, u8 id, u8 storm,
				      u16 index, u8 op, u8 update)
{
	struct bnx2x *bp = netdev_priv(dev->netdev);
	u32 hc_addr = (HC_REG_COMMAND_REG + BP_PORT(bp) * 32 +
		       COMMAND_REG_INT_ACK);
	struct igu_ack_register igu_ack;

	igu_ack.status_block_index = index;
	igu_ack.sb_id_and_flags =
			((id << IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT) |
			 (storm << IGU_ACK_REGISTER_STORM_ID_SHIFT) |
			 (update << IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT) |
			 (op << IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT));

	CNIC_WR(dev, hc_addr, (*(u32 *)&igu_ack));
}