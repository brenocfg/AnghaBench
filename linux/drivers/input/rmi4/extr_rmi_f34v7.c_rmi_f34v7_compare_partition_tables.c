#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ui_firmware; scalar_t__ ui_config; scalar_t__ dp_config; scalar_t__ guest_code; } ;
struct TYPE_7__ {TYPE_2__ phyaddr; } ;
struct TYPE_5__ {scalar_t__ ui_firmware; scalar_t__ ui_config; scalar_t__ dp_config; scalar_t__ guest_code; } ;
struct TYPE_8__ {int new_partition_table; TYPE_3__ img; TYPE_1__ phyaddr; scalar_t__ has_guest_code; scalar_t__ has_display_cfg; } ;
struct f34_data {TYPE_4__ v7; } ;

/* Variables and functions */

__attribute__((used)) static void rmi_f34v7_compare_partition_tables(struct f34_data *f34)
{
	if (f34->v7.phyaddr.ui_firmware != f34->v7.img.phyaddr.ui_firmware) {
		f34->v7.new_partition_table = true;
		return;
	}

	if (f34->v7.phyaddr.ui_config != f34->v7.img.phyaddr.ui_config) {
		f34->v7.new_partition_table = true;
		return;
	}

	if (f34->v7.has_display_cfg &&
	    f34->v7.phyaddr.dp_config != f34->v7.img.phyaddr.dp_config) {
		f34->v7.new_partition_table = true;
		return;
	}

	if (f34->v7.has_guest_code &&
	    f34->v7.phyaddr.guest_code != f34->v7.img.phyaddr.guest_code) {
		f34->v7.new_partition_table = true;
		return;
	}

	f34->v7.new_partition_table = false;
}