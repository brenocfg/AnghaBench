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
struct ipmi_user {struct ipmi_smi* intf; } ;
struct ipmi_smi {int maintenance_mode; int maintenance_mode_enable; int /*<<< orphan*/  maintenance_mode_lock; int /*<<< orphan*/  auto_maintenance_timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  IPMI_MAINTENANCE_MODE_AUTO 130 
#define  IPMI_MAINTENANCE_MODE_OFF 129 
#define  IPMI_MAINTENANCE_MODE_ON 128 
 struct ipmi_user* acquire_ipmi_user (struct ipmi_user*,int*) ; 
 int /*<<< orphan*/  maintenance_mode_update (struct ipmi_smi*) ; 
 int /*<<< orphan*/  release_ipmi_user (struct ipmi_user*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipmi_set_maintenance_mode(struct ipmi_user *user, int mode)
{
	int rv = 0, index;
	unsigned long flags;
	struct ipmi_smi *intf = user->intf;

	user = acquire_ipmi_user(user, &index);
	if (!user)
		return -ENODEV;

	spin_lock_irqsave(&intf->maintenance_mode_lock, flags);
	if (intf->maintenance_mode != mode) {
		switch (mode) {
		case IPMI_MAINTENANCE_MODE_AUTO:
			intf->maintenance_mode_enable
				= (intf->auto_maintenance_timeout > 0);
			break;

		case IPMI_MAINTENANCE_MODE_OFF:
			intf->maintenance_mode_enable = false;
			break;

		case IPMI_MAINTENANCE_MODE_ON:
			intf->maintenance_mode_enable = true;
			break;

		default:
			rv = -EINVAL;
			goto out_unlock;
		}
		intf->maintenance_mode = mode;

		maintenance_mode_update(intf);
	}
 out_unlock:
	spin_unlock_irqrestore(&intf->maintenance_mode_lock, flags);
	release_ipmi_user(user, index);

	return rv;
}