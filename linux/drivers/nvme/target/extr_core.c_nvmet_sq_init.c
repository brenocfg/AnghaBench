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
struct nvmet_sq {int /*<<< orphan*/  confirm_done; int /*<<< orphan*/  free_done; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_sq_free ; 
 int percpu_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int nvmet_sq_init(struct nvmet_sq *sq)
{
	int ret;

	ret = percpu_ref_init(&sq->ref, nvmet_sq_free, 0, GFP_KERNEL);
	if (ret) {
		pr_err("percpu_ref init failed!\n");
		return ret;
	}
	init_completion(&sq->free_done);
	init_completion(&sq->confirm_done);

	return 0;
}