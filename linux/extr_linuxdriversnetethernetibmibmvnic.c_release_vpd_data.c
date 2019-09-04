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
struct ibmvnic_adapter {TYPE_1__* vpd; } ;
struct TYPE_2__ {struct TYPE_2__* buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void release_vpd_data(struct ibmvnic_adapter *adapter)
{
	if (!adapter->vpd)
		return;

	kfree(adapter->vpd->buff);
	kfree(adapter->vpd);

	adapter->vpd = NULL;
}