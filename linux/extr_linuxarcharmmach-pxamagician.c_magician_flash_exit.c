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

/* Variables and functions */
 int /*<<< orphan*/  EGPIO_MAGICIAN_FLASH_VPP ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void magician_flash_exit(struct platform_device *pdev)
{
	gpio_free(EGPIO_MAGICIAN_FLASH_VPP);
}