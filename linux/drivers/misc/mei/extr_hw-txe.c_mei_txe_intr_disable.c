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
struct mei_txe_hw {int dummy; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HHIER_REG ; 
 int /*<<< orphan*/  HIER_REG ; 
 int /*<<< orphan*/  mei_txe_br_reg_write (struct mei_txe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static void mei_txe_intr_disable(struct mei_device *dev)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_br_reg_write(hw, HHIER_REG, 0);
	mei_txe_br_reg_write(hw, HIER_REG, 0);
}