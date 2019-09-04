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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_84XX_VNIC_COUNT ; 
 int /*<<< orphan*/  QLC_DEFAULT_VNIC_COUNT ; 
 scalar_t__ qlcnic_84xx_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static inline u32 qlcnic_get_vnic_func_count(struct qlcnic_adapter *adapter)
{
	if (qlcnic_84xx_check(adapter))
		return QLC_84XX_VNIC_COUNT;
	else
		return QLC_DEFAULT_VNIC_COUNT;
}