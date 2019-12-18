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
struct tb {TYPE_1__* cm_ops; } ;
struct TYPE_2__ {int (* disconnect_pcie_paths ) (struct tb*) ;} ;

/* Variables and functions */
 int EPERM ; 
 int stub1 (struct tb*) ; 

int tb_domain_disconnect_pcie_paths(struct tb *tb)
{
	if (!tb->cm_ops->disconnect_pcie_paths)
		return -EPERM;

	return tb->cm_ops->disconnect_pcie_paths(tb);
}