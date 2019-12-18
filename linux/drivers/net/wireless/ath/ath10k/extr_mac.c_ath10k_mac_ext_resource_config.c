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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_1__ wmi; } ;
typedef  enum wmi_host_platform_type { ____Placeholder_wmi_host_platform_type } wmi_host_platform_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WMI_HOST_PLATFORM_HIGH_PERF ; 
 int WMI_HOST_PLATFORM_LOW_PERF ; 
 int /*<<< orphan*/  WMI_SERVICE_TX_MODE_DYNAMIC ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_ext_resource_config (struct ath10k*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_mac_ext_resource_config(struct ath10k *ar, u32 val)
{
	enum wmi_host_platform_type platform_type;
	int ret;

	if (test_bit(WMI_SERVICE_TX_MODE_DYNAMIC, ar->wmi.svc_map))
		platform_type = WMI_HOST_PLATFORM_LOW_PERF;
	else
		platform_type = WMI_HOST_PLATFORM_HIGH_PERF;

	ret = ath10k_wmi_ext_resource_config(ar, platform_type, val);

	if (ret && ret != -EOPNOTSUPP) {
		ath10k_warn(ar, "failed to configure ext resource: %d\n", ret);
		return ret;
	}

	return 0;
}