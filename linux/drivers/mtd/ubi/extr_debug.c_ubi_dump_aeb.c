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
struct ubi_ainf_peb {int /*<<< orphan*/  sqnum; int /*<<< orphan*/  scrub; int /*<<< orphan*/  lnum; int /*<<< orphan*/  pnum; int /*<<< orphan*/  ec; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,...) ; 

void ubi_dump_aeb(const struct ubi_ainf_peb *aeb, int type)
{
	pr_err("eraseblock attaching information dump:\n");
	pr_err("\tec       %d\n", aeb->ec);
	pr_err("\tpnum     %d\n", aeb->pnum);
	if (type == 0) {
		pr_err("\tlnum     %d\n", aeb->lnum);
		pr_err("\tscrub    %d\n", aeb->scrub);
		pr_err("\tsqnum    %llu\n", aeb->sqnum);
	}
}