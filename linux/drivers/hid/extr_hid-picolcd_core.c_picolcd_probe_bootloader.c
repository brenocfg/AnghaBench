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
struct picolcd_data {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_BL_READ_MEMORY ; 
 int /*<<< orphan*/  REPORT_BL_WRITE_MEMORY ; 
 int /*<<< orphan*/  picolcd_init_devfs (struct picolcd_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picolcd_out_report (int /*<<< orphan*/ ,struct hid_device*) ; 

__attribute__((used)) static int picolcd_probe_bootloader(struct hid_device *hdev, struct picolcd_data *data)
{
	picolcd_init_devfs(data, NULL, NULL,
			picolcd_out_report(REPORT_BL_READ_MEMORY, hdev),
			picolcd_out_report(REPORT_BL_WRITE_MEMORY, hdev), NULL);
	return 0;
}