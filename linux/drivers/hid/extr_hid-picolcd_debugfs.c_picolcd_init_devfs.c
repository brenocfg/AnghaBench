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
struct picolcd_data {int addr_sz; void* debug_flash; void* debug_eeprom; void* debug_reset; int /*<<< orphan*/  mutex_flash; struct hid_device* hdev; } ;
struct hid_report {int maxfield; TYPE_1__** field; } ;
struct hid_device {int /*<<< orphan*/  debug_dir; } ;
struct TYPE_2__ {int report_size; int report_count; } ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct picolcd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picolcd_debug_eeprom_fops ; 
 int /*<<< orphan*/  picolcd_debug_flash_fops ; 
 int /*<<< orphan*/  picolcd_debug_reset_fops ; 

void picolcd_init_devfs(struct picolcd_data *data,
		struct hid_report *eeprom_r, struct hid_report *eeprom_w,
		struct hid_report *flash_r, struct hid_report *flash_w,
		struct hid_report *reset)
{
	struct hid_device *hdev = data->hdev;

	mutex_init(&data->mutex_flash);

	/* reset */
	if (reset)
		data->debug_reset = debugfs_create_file("reset", 0600,
				hdev->debug_dir, data, &picolcd_debug_reset_fops);

	/* eeprom */
	if (eeprom_r || eeprom_w)
		data->debug_eeprom = debugfs_create_file("eeprom",
			(eeprom_w ? S_IWUSR : 0) | (eeprom_r ? S_IRUSR : 0),
			hdev->debug_dir, data, &picolcd_debug_eeprom_fops);

	/* flash */
	if (flash_r && flash_r->maxfield == 1 && flash_r->field[0]->report_size == 8)
		data->addr_sz = flash_r->field[0]->report_count - 1;
	else
		data->addr_sz = -1;
	if (data->addr_sz == 2 || data->addr_sz == 3) {
		data->debug_flash = debugfs_create_file("flash",
			(flash_w ? S_IWUSR : 0) | (flash_r ? S_IRUSR : 0),
			hdev->debug_dir, data, &picolcd_debug_flash_fops);
	} else if (flash_r || flash_w)
		hid_warn(hdev, "Unexpected FLASH access reports, please submit rdesc for review\n");
}