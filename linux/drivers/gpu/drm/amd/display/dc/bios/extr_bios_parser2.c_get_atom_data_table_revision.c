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
typedef  int uint32_t ;
struct atom_data_revision {int major; int minor; } ;
struct atom_common_table_header {scalar_t__ content_revision; scalar_t__ format_revision; } ;

/* Variables and functions */

__attribute__((used)) static void get_atom_data_table_revision(
	struct atom_common_table_header *atom_data_tbl,
	struct atom_data_revision *tbl_revision)
{
	if (!tbl_revision)
		return;

	/* initialize the revision to 0 which is invalid revision */
	tbl_revision->major = 0;
	tbl_revision->minor = 0;

	if (!atom_data_tbl)
		return;

	tbl_revision->major =
			(uint32_t) atom_data_tbl->format_revision & 0x3f;
	tbl_revision->minor =
			(uint32_t) atom_data_tbl->content_revision & 0x3f;
}