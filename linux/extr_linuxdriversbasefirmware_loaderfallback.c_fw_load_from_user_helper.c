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
struct fw_sysfs {int /*<<< orphan*/  fw_priv; } ;
struct firmware {int /*<<< orphan*/  priv; } ;
struct device {int dummy; } ;
typedef  enum fw_opt { ____Placeholder_fw_opt } fw_opt ;

/* Variables and functions */
 int EBUSY ; 
 int FW_OPT_NOWAIT ; 
 scalar_t__ IS_ERR (struct fw_sysfs*) ; 
 int PTR_ERR (struct fw_sysfs*) ; 
 scalar_t__ WARN_ON (int) ; 
 int assign_fw (struct firmware*,struct device*,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 long firmware_loading_timeout () ; 
 struct fw_sysfs* fw_create_instance (struct firmware*,char const*,struct device*,int) ; 
 int fw_load_sysfs_fallback (struct fw_sysfs*,int,long) ; 
 long usermodehelper_read_lock_wait (long) ; 
 int usermodehelper_read_trylock () ; 
 int /*<<< orphan*/  usermodehelper_read_unlock () ; 

__attribute__((used)) static int fw_load_from_user_helper(struct firmware *firmware,
				    const char *name, struct device *device,
				    enum fw_opt opt_flags)
{
	struct fw_sysfs *fw_sysfs;
	long timeout;
	int ret;

	timeout = firmware_loading_timeout();
	if (opt_flags & FW_OPT_NOWAIT) {
		timeout = usermodehelper_read_lock_wait(timeout);
		if (!timeout) {
			dev_dbg(device, "firmware: %s loading timed out\n",
				name);
			return -EBUSY;
		}
	} else {
		ret = usermodehelper_read_trylock();
		if (WARN_ON(ret)) {
			dev_err(device, "firmware: %s will not be loaded\n",
				name);
			return ret;
		}
	}

	fw_sysfs = fw_create_instance(firmware, name, device, opt_flags);
	if (IS_ERR(fw_sysfs)) {
		ret = PTR_ERR(fw_sysfs);
		goto out_unlock;
	}

	fw_sysfs->fw_priv = firmware->priv;
	ret = fw_load_sysfs_fallback(fw_sysfs, opt_flags, timeout);

	if (!ret)
		ret = assign_fw(firmware, device, opt_flags);

out_unlock:
	usermodehelper_read_unlock();

	return ret;
}