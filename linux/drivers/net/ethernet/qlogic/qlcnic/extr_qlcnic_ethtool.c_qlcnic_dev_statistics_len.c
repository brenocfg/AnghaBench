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
struct qlcnic_adapter {int flags; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int QLCNIC_ESWITCH_ENABLED ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_82xx_statistics (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_statistics (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_device_gstrings_stats ; 

__attribute__((used)) static int qlcnic_dev_statistics_len(struct qlcnic_adapter *adapter)
{
	int len = -1;

	if (qlcnic_82xx_check(adapter)) {
		len = qlcnic_82xx_statistics(adapter);
		if (adapter->flags & QLCNIC_ESWITCH_ENABLED)
			len += ARRAY_SIZE(qlcnic_device_gstrings_stats);
	} else if (qlcnic_83xx_check(adapter)) {
		len = qlcnic_83xx_statistics(adapter);
	}

	return len;
}