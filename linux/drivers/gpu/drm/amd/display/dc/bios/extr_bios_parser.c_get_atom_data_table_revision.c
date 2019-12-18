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
typedef  void* uint32_t ;
struct atom_data_revision {void* minor; void* major; } ;
typedef  int /*<<< orphan*/  ATOM_COMMON_TABLE_HEADER ;

/* Variables and functions */
 scalar_t__ GET_DATA_TABLE_MAJOR_REVISION (int /*<<< orphan*/ *) ; 
 scalar_t__ GET_DATA_TABLE_MINOR_REVISION (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_atom_data_table_revision(
	ATOM_COMMON_TABLE_HEADER *atom_data_tbl,
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
			(uint32_t) GET_DATA_TABLE_MAJOR_REVISION(atom_data_tbl);
	tbl_revision->minor =
			(uint32_t) GET_DATA_TABLE_MINOR_REVISION(atom_data_tbl);
}