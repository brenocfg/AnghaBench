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
struct ubi_vtbl_record {char* name; int /*<<< orphan*/  crc; scalar_t__ upd_marker; scalar_t__ vol_type; int /*<<< orphan*/  data_pad; int /*<<< orphan*/  alignment; int /*<<< orphan*/  reserved_pebs; int /*<<< orphan*/  name_len; } ;

/* Variables and functions */
 int UBI_VOL_NAME_MAX ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 char* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int strnlen (char*,int) ; 

void ubi_dump_vtbl_record(const struct ubi_vtbl_record *r, int idx)
{
	int name_len = be16_to_cpu(r->name_len);

	pr_err("Volume table record %d dump:\n", idx);
	pr_err("\treserved_pebs   %d\n", be32_to_cpu(r->reserved_pebs));
	pr_err("\talignment       %d\n", be32_to_cpu(r->alignment));
	pr_err("\tdata_pad        %d\n", be32_to_cpu(r->data_pad));
	pr_err("\tvol_type        %d\n", (int)r->vol_type);
	pr_err("\tupd_marker      %d\n", (int)r->upd_marker);
	pr_err("\tname_len        %d\n", name_len);

	if (r->name[0] == '\0') {
		pr_err("\tname            NULL\n");
		return;
	}

	if (name_len <= UBI_VOL_NAME_MAX &&
	    strnlen(&r->name[0], name_len + 1) == name_len) {
		pr_err("\tname            %s\n", &r->name[0]);
	} else {
		pr_err("\t1st 5 characters of name: %c%c%c%c%c\n",
			r->name[0], r->name[1], r->name[2], r->name[3],
			r->name[4]);
	}
	pr_err("\tcrc             %#08x\n", be32_to_cpu(r->crc));
}