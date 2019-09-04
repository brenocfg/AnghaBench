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
struct be_adapter {scalar_t__ db; } ;

/* Variables and functions */
 scalar_t__ PHYSDEV_CONTROL_OFFSET ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int lancer_wait_idle (struct be_adapter*) ; 

int lancer_physdev_ctrl(struct be_adapter *adapter, u32 mask)
{
	int status = 0;

	status = lancer_wait_idle(adapter);
	if (status)
		return status;

	iowrite32(mask, adapter->db + PHYSDEV_CONTROL_OFFSET);

	return status;
}