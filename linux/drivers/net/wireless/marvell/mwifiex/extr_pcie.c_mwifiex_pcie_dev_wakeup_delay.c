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
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ mwifiex_pcie_ok_to_access_hw (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mwifiex_pcie_dev_wakeup_delay(struct mwifiex_adapter *adapter)
{
	int i = 0;

	while (mwifiex_pcie_ok_to_access_hw(adapter)) {
		i++;
		usleep_range(10, 20);
		/* 50ms max wait */
		if (i == 5000)
			break;
	}

	return;
}