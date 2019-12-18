#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int (* enqueue_tx ) (struct fm10k_hw*,struct fm10k_mbx_info*,scalar_t__*) ;int /*<<< orphan*/  (* process ) (struct fm10k_hw*,struct fm10k_mbx_info*) ;} ;
struct fm10k_mbx_info {int test_result; TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct fm10k_hw {TYPE_1__ mac; struct fm10k_mbx_info mbx; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int EINVAL ; 
 int FM10K_NOT_IMPLEMENTED ; 
 int FM10K_TEST_MSG_NESTED ; 
 int FM10K_TEST_MSG_UNSET ; 
 unsigned long HZ ; 
 scalar_t__ fm10k_mac_vf ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_tlv_msg_test_create (scalar_t__*,scalar_t__) ; 
 unsigned long jiffies ; 
 int stub1 (struct fm10k_hw*,struct fm10k_mbx_info*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int fm10k_mbx_test(struct fm10k_intfc *interface, u64 *data)
{
	struct fm10k_hw *hw = &interface->hw;
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 attr_flag, test_msg[6];
	unsigned long timeout;
	int err = -EINVAL;

	/* For now this is a VF only feature */
	if (hw->mac.type != fm10k_mac_vf)
		return 0;

	/* loop through both nested and unnested attribute types */
	for (attr_flag = BIT(FM10K_TEST_MSG_UNSET);
	     attr_flag < BIT(2 * FM10K_TEST_MSG_NESTED);
	     attr_flag += attr_flag) {
		/* generate message to be tested */
		fm10k_tlv_msg_test_create(test_msg, attr_flag);

		fm10k_mbx_lock(interface);
		mbx->test_result = FM10K_NOT_IMPLEMENTED;
		err = mbx->ops.enqueue_tx(hw, mbx, test_msg);
		fm10k_mbx_unlock(interface);

		/* wait up to 1 second for response */
		timeout = jiffies + HZ;
		do {
			if (err < 0)
				goto err_out;

			usleep_range(500, 1000);

			fm10k_mbx_lock(interface);
			mbx->ops.process(hw, mbx);
			fm10k_mbx_unlock(interface);

			err = mbx->test_result;
			if (!err)
				break;
		} while (time_is_after_jiffies(timeout));

		/* reporting errors */
		if (err)
			goto err_out;
	}

err_out:
	*data = err < 0 ? (attr_flag) : (err > 0);
	return err;
}