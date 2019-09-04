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
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ FLASH_IMG_READY ; 
 TYPE_2__ image_data ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_alert (char*,...) ; 
 TYPE_1__ update_flash_data ; 

void opal_flash_update_print_message(void)
{
	if (update_flash_data.status != FLASH_IMG_READY)
		return;

	pr_alert("FLASH: Flashing new firmware\n");
	pr_alert("FLASH: Image is %u bytes\n", image_data.size);
	pr_alert("FLASH: Performing flash and reboot/shutdown\n");
	pr_alert("FLASH: This will take several minutes. Do not power off!\n");

	/* Small delay to help getting the above message out */
	msleep(500);
}