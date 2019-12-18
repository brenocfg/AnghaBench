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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  hotkey; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int ERESTARTSYS ; 
 int hotkey_all_mask ; 
 int /*<<< orphan*/  hotkey_enabledisable_warn (int) ; 
 int /*<<< orphan*/  hotkey_mutex ; 
 int hotkey_reserved_mask ; 
 int hotkey_source_mask ; 
 int hotkey_user_mask ; 
 int hotkey_user_mask_set (int) ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 char* next_cmd (char**) ; 
 int sscanf (char*,char*,int*) ; 
 scalar_t__ strlencmp (char*,char*) ; 
 TYPE_1__ tp_features ; 
 int /*<<< orphan*/  tpacpi_disclose_usertask (char*,char*,int) ; 

__attribute__((used)) static int hotkey_write(char *buf)
{
	int res;
	u32 mask;
	char *cmd;

	if (!tp_features.hotkey)
		return -ENODEV;

	if (mutex_lock_killable(&hotkey_mutex))
		return -ERESTARTSYS;

	mask = hotkey_user_mask;

	res = 0;
	while ((cmd = next_cmd(&buf))) {
		if (strlencmp(cmd, "enable") == 0) {
			hotkey_enabledisable_warn(1);
		} else if (strlencmp(cmd, "disable") == 0) {
			hotkey_enabledisable_warn(0);
			res = -EPERM;
		} else if (strlencmp(cmd, "reset") == 0) {
			mask = (hotkey_all_mask | hotkey_source_mask)
				& ~hotkey_reserved_mask;
		} else if (sscanf(cmd, "0x%x", &mask) == 1) {
			/* mask set */
		} else if (sscanf(cmd, "%x", &mask) == 1) {
			/* mask set */
		} else {
			res = -EINVAL;
			goto errexit;
		}
	}

	if (!res) {
		tpacpi_disclose_usertask("procfs hotkey",
			"set mask to 0x%08x\n", mask);
		res = hotkey_user_mask_set(mask);
	}

errexit:
	mutex_unlock(&hotkey_mutex);
	return res;
}