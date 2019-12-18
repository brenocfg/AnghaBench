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
struct atl1_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int atl1_init_hw (int /*<<< orphan*/ *) ; 
 int atl1_reset_hw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1_reset(struct atl1_adapter *adapter)
{
	int ret;
	ret = atl1_reset_hw(&adapter->hw);
	if (ret)
		return ret;
	return atl1_init_hw(&adapter->hw);
}