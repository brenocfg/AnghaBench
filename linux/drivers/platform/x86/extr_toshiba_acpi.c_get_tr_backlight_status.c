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
typedef  scalar_t__ u32 ;
struct toshiba_acpi_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  HCI_TR_BACKLIGHT ; 
 scalar_t__ TOS_FAILURE ; 
 scalar_t__ TOS_NOT_SUPPORTED ; 
 scalar_t__ TOS_SUCCESS ; 
 scalar_t__ hci_read (struct toshiba_acpi_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int get_tr_backlight_status(struct toshiba_acpi_dev *dev, u32 *status)
{
	u32 result = hci_read(dev, HCI_TR_BACKLIGHT, status);

	if (result == TOS_FAILURE)
		pr_err("ACPI call to get Transflective Backlight failed\n");
	else if (result == TOS_NOT_SUPPORTED)
		return -ENODEV;

	return result == TOS_SUCCESS ? 0 : -EIO;
}