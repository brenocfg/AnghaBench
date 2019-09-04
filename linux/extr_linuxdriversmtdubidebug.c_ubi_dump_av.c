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
struct ubi_ainf_volume {int /*<<< orphan*/  data_pad; int /*<<< orphan*/  last_data_size; int /*<<< orphan*/  used_ebs; int /*<<< orphan*/  vol_type; int /*<<< orphan*/  compat; int /*<<< orphan*/  leb_count; int /*<<< orphan*/  highest_lnum; int /*<<< orphan*/  vol_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,...) ; 

void ubi_dump_av(const struct ubi_ainf_volume *av)
{
	pr_err("Volume attaching information dump:\n");
	pr_err("\tvol_id         %d\n", av->vol_id);
	pr_err("\thighest_lnum   %d\n", av->highest_lnum);
	pr_err("\tleb_count      %d\n", av->leb_count);
	pr_err("\tcompat         %d\n", av->compat);
	pr_err("\tvol_type       %d\n", av->vol_type);
	pr_err("\tused_ebs       %d\n", av->used_ebs);
	pr_err("\tlast_data_size %d\n", av->last_data_size);
	pr_err("\tdata_pad       %d\n", av->data_pad);
}