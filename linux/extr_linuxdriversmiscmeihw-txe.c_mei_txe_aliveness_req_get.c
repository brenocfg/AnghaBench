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
struct mei_txe_hw {int dummy; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SICR_HOST_ALIVENESS_REQ_REG ; 
 int SICR_HOST_ALIVENESS_REQ_REQUESTED ; 
 int mei_txe_br_reg_read (struct mei_txe_hw*,int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static u32 mei_txe_aliveness_req_get(struct mei_device *dev)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);
	u32 reg;

	reg = mei_txe_br_reg_read(hw, SICR_HOST_ALIVENESS_REQ_REG);
	return reg & SICR_HOST_ALIVENESS_REQ_REQUESTED;
}