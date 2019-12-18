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
struct super_block {int /*<<< orphan*/  s_flags; } ;
struct exfat_mount_options {scalar_t__ errors; } ;
struct TYPE_2__ {struct exfat_mount_options options; } ;

/* Variables and functions */
 scalar_t__ EXFAT_ERRORS_PANIC ; 
 scalar_t__ EXFAT_ERRORS_RO ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

void fs_error(struct super_block *sb)
{
	struct exfat_mount_options *opts = &EXFAT_SB(sb)->options;

	if (opts->errors == EXFAT_ERRORS_PANIC) {
		panic("[EXFAT] Filesystem panic from previous error\n");
	} else if ((opts->errors == EXFAT_ERRORS_RO) && !sb_rdonly(sb)) {
		sb->s_flags |= SB_RDONLY;
		pr_err("[EXFAT] Filesystem has been set read-only\n");
	}
}