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
typedef  int u32 ;
struct be_adapter {int cmd_privileges; } ;

/* Variables and functions */

__attribute__((used)) static inline bool check_privilege(struct be_adapter *adapter, u32 flags)
{
	return flags & adapter->cmd_privileges ? true : false;
}