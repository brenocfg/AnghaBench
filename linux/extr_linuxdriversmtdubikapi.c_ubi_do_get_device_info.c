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
struct ubi_device_info {int /*<<< orphan*/  cdev; int /*<<< orphan*/  ro_mode; int /*<<< orphan*/  max_write_size; int /*<<< orphan*/  min_io_size; int /*<<< orphan*/  leb_start; int /*<<< orphan*/  leb_size; int /*<<< orphan*/  ubi_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ubi_device {TYPE_1__ cdev; int /*<<< orphan*/  ro_mode; int /*<<< orphan*/  max_write_size; int /*<<< orphan*/  min_io_size; int /*<<< orphan*/  leb_start; int /*<<< orphan*/  leb_size; int /*<<< orphan*/  ubi_num; } ;

/* Variables and functions */

void ubi_do_get_device_info(struct ubi_device *ubi, struct ubi_device_info *di)
{
	di->ubi_num = ubi->ubi_num;
	di->leb_size = ubi->leb_size;
	di->leb_start = ubi->leb_start;
	di->min_io_size = ubi->min_io_size;
	di->max_write_size = ubi->max_write_size;
	di->ro_mode = ubi->ro_mode;
	di->cdev = ubi->cdev.dev;
}