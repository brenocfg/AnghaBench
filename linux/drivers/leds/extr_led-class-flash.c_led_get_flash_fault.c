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
struct led_classdev_flash {int dummy; } ;

/* Variables and functions */
 int call_flash_op (struct led_classdev_flash*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fault_get ; 

int led_get_flash_fault(struct led_classdev_flash *fled_cdev, u32 *fault)
{
	return call_flash_op(fled_cdev, fault_get, fault);
}