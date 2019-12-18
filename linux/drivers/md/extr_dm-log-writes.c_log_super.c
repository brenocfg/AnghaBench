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
typedef  int /*<<< orphan*/  super ;
struct log_writes_c {int /*<<< orphan*/  super_done; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  logged_entries; } ;
struct log_write_super {int /*<<< orphan*/  sectorsize; void* nr_entries; void* version; void* magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  WRITE_LOG_MAGIC ; 
 int /*<<< orphan*/  WRITE_LOG_SUPER_SECTOR ; 
 int /*<<< orphan*/  WRITE_LOG_VERSION ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 
 scalar_t__ write_metadata (struct log_writes_c*,struct log_write_super*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int log_super(struct log_writes_c *lc)
{
	struct log_write_super super;

	super.magic = cpu_to_le64(WRITE_LOG_MAGIC);
	super.version = cpu_to_le64(WRITE_LOG_VERSION);
	super.nr_entries = cpu_to_le64(lc->logged_entries);
	super.sectorsize = cpu_to_le32(lc->sectorsize);

	if (write_metadata(lc, &super, sizeof(super), NULL, 0,
			   WRITE_LOG_SUPER_SECTOR)) {
		DMERR("Couldn't write super");
		return -1;
	}

	/*
	 * Super sector should be writen in-order, otherwise the
	 * nr_entries could be rewritten incorrectly by an old bio.
	 */
	wait_for_completion_io(&lc->super_done);

	return 0;
}