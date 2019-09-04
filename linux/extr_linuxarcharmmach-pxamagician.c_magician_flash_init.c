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
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int magician_flash_init(struct platform_device *pdev)
{
	int ret = gpio_request(EGPIO_MAGICIAN_FLASH_VPP, "flash Vpp enable");

	if (ret) {
		pr_err("Cannot request flash enable GPIO (%i)\n", ret);
		return ret;
	}

	ret = gpio_direction_output(EGPIO_MAGICIAN_FLASH_VPP, 1);
	if (ret) {
		pr_err("Cannot set direction for flash enable (%i)\n", ret);
		gpio_free(EGPIO_MAGICIAN_FLASH_VPP);
	}

	return ret;
}