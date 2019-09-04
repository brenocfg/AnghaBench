#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * fhead; scalar_t__ fmax; } ;
struct TYPE_3__ {scalar_t__ fmax; int /*<<< orphan*/ * fhead; } ;
struct qlcnic_adapter {TYPE_2__ rx_fhash; TYPE_1__ fhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_free_lb_filters_mem(struct qlcnic_adapter *adapter)
{
	if (adapter->fhash.fmax)
		kfree(adapter->fhash.fhead);

	adapter->fhash.fhead = NULL;
	adapter->fhash.fmax = 0;

	if (adapter->rx_fhash.fmax)
		kfree(adapter->rx_fhash.fhead);

	adapter->rx_fhash.fmax = 0;
	adapter->rx_fhash.fhead = NULL;
}