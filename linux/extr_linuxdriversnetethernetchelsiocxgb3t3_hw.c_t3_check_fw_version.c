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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int EINVAL ; 
 unsigned int FW_VERSION_MAJOR ; 
 unsigned int FW_VERSION_MINOR ; 
 unsigned int FW_VERSION_T3 ; 
 unsigned int G_FW_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 unsigned int G_FW_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 unsigned int G_FW_VERSION_TYPE (int /*<<< orphan*/ ) ; 
 int t3_get_fw_version (struct adapter*,int /*<<< orphan*/ *) ; 

int t3_check_fw_version(struct adapter *adapter)
{
	int ret;
	u32 vers;
	unsigned int type, major, minor;

	ret = t3_get_fw_version(adapter, &vers);
	if (ret)
		return ret;

	type = G_FW_VERSION_TYPE(vers);
	major = G_FW_VERSION_MAJOR(vers);
	minor = G_FW_VERSION_MINOR(vers);

	if (type == FW_VERSION_T3 && major == FW_VERSION_MAJOR &&
	    minor == FW_VERSION_MINOR)
		return 0;
	else if (major != FW_VERSION_MAJOR || minor < FW_VERSION_MINOR)
		CH_WARN(adapter, "found old FW minor version(%u.%u), "
		        "driver compiled for version %u.%u\n", major, minor,
			FW_VERSION_MAJOR, FW_VERSION_MINOR);
	else {
		CH_WARN(adapter, "found newer FW version(%u.%u), "
		        "driver compiled for version %u.%u\n", major, minor,
			FW_VERSION_MAJOR, FW_VERSION_MINOR);
			return 0;
	}
	return -EINVAL;
}