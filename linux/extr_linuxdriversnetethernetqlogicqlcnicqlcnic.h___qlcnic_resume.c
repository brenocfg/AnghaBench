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
struct qlcnic_adapter {TYPE_1__* nic_ops; } ;
struct TYPE_2__ {int (* resume ) (struct qlcnic_adapter*) ;} ;

/* Variables and functions */
 int stub1 (struct qlcnic_adapter*) ; 

__attribute__((used)) static inline int __qlcnic_resume(struct qlcnic_adapter *adapter)
{
	return adapter->nic_ops->resume(adapter);
}