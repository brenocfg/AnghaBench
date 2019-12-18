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

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_DS ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

void lkdtm_CORRUPT_USER_DS(void)
{
	pr_info("setting bad task size limit\n");
	set_fs(KERNEL_DS);

	/* Make sure we do not keep running with a KERNEL_DS! */
	force_sig(SIGKILL);
}