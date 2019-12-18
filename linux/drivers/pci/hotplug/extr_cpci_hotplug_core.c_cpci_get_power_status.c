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
typedef  int u8 ;
struct slot {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_power ) (struct slot*) ;} ;

/* Variables and functions */
 TYPE_2__* controller ; 
 int stub1 (struct slot*) ; 

__attribute__((used)) static u8
cpci_get_power_status(struct slot *slot)
{
	u8 power = 1;

	if (controller->ops->get_power)
		power = controller->ops->get_power(slot);
	return power;
}