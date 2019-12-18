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
struct platform_device {int dummy; } ;
struct nic78bx_led_data {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ NIC78BX_LOCK_REG_OFFSET ; 
 int /*<<< orphan*/  NIC78BX_LOCK_VALUE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 struct nic78bx_led_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int nic78bx_remove(struct platform_device *pdev)
{
	struct nic78bx_led_data *led_data = platform_get_drvdata(pdev);

	/* Lock LED register */
	outb(NIC78BX_LOCK_VALUE,
	     led_data->io_base + NIC78BX_LOCK_REG_OFFSET);

	return 0;
}