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
struct ubi_volume_info {int /*<<< orphan*/  cdev; int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; int /*<<< orphan*/  usable_leb_size; int /*<<< orphan*/  alignment; int /*<<< orphan*/  upd_marker; int /*<<< orphan*/  corrupted; int /*<<< orphan*/  vol_type; int /*<<< orphan*/  used_bytes; int /*<<< orphan*/  size; int /*<<< orphan*/  ubi_num; int /*<<< orphan*/  vol_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ubi_volume {TYPE_1__ cdev; int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; int /*<<< orphan*/  usable_leb_size; int /*<<< orphan*/  alignment; int /*<<< orphan*/  upd_marker; int /*<<< orphan*/  corrupted; int /*<<< orphan*/  vol_type; int /*<<< orphan*/  used_bytes; int /*<<< orphan*/  reserved_pebs; int /*<<< orphan*/  vol_id; } ;
struct ubi_device {int /*<<< orphan*/  ubi_num; } ;

/* Variables and functions */

void ubi_do_get_volume_info(struct ubi_device *ubi, struct ubi_volume *vol,
			    struct ubi_volume_info *vi)
{
	vi->vol_id = vol->vol_id;
	vi->ubi_num = ubi->ubi_num;
	vi->size = vol->reserved_pebs;
	vi->used_bytes = vol->used_bytes;
	vi->vol_type = vol->vol_type;
	vi->corrupted = vol->corrupted;
	vi->upd_marker = vol->upd_marker;
	vi->alignment = vol->alignment;
	vi->usable_leb_size = vol->usable_leb_size;
	vi->name_len = vol->name_len;
	vi->name = vol->name;
	vi->cdev = vol->cdev.dev;
}