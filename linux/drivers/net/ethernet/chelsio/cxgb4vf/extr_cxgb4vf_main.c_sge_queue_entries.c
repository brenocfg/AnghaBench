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
struct TYPE_2__ {int /*<<< orphan*/  ethqsets; } ;
struct adapter {int flags; TYPE_1__ sge; } ;

/* Variables and functions */
 int CXGB4VF_USING_MSI ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPL ; 

__attribute__((used)) static int sge_queue_entries(const struct adapter *adapter)
{
	return DIV_ROUND_UP(adapter->sge.ethqsets, QPL) + 1 +
		((adapter->flags & CXGB4VF_USING_MSI) != 0);
}