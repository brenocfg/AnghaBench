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
typedef  int /*<<< orphan*/  u16 ;
struct i40iw_cm_core {int /*<<< orphan*/  apbvt_lock; int /*<<< orphan*/  ports_in_use; } ;
struct i40iw_device {struct i40iw_cm_core cm_core; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40iw_cqp_manage_abvpt_cmd (struct i40iw_device*,int /*<<< orphan*/ ,int) ; 
 int i40iw_port_in_use (struct i40iw_cm_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

enum i40iw_status_code i40iw_manage_apbvt(struct i40iw_device *iwdev,
					  u16 accel_local_port,
					  bool add_port)
{
	struct i40iw_cm_core *cm_core = &iwdev->cm_core;
	enum i40iw_status_code status;
	unsigned long flags;
	bool in_use;

	/* apbvt_lock is held across CQP delete APBVT OP (non-waiting) to
	 * protect against race where add APBVT CQP can race ahead of the delete
	 * APBVT for same port.
	 */
	if (add_port) {
		spin_lock_irqsave(&cm_core->apbvt_lock, flags);
		in_use = __test_and_set_bit(accel_local_port,
					    cm_core->ports_in_use);
		spin_unlock_irqrestore(&cm_core->apbvt_lock, flags);
		if (in_use)
			return 0;
		return i40iw_cqp_manage_abvpt_cmd(iwdev, accel_local_port,
						  true);
	} else {
		spin_lock_irqsave(&cm_core->apbvt_lock, flags);
		in_use = i40iw_port_in_use(cm_core, accel_local_port);
		if (in_use) {
			spin_unlock_irqrestore(&cm_core->apbvt_lock, flags);
			return 0;
		}
		__clear_bit(accel_local_port, cm_core->ports_in_use);
		status = i40iw_cqp_manage_abvpt_cmd(iwdev, accel_local_port,
						    false);
		spin_unlock_irqrestore(&cm_core->apbvt_lock, flags);
		return status;
	}
}