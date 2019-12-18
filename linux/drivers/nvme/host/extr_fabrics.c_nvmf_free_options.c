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
struct nvmf_ctrl_options {struct nvmf_ctrl_options* host_traddr; struct nvmf_ctrl_options* subsysnqn; struct nvmf_ctrl_options* trsvcid; struct nvmf_ctrl_options* traddr; struct nvmf_ctrl_options* transport; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvmf_ctrl_options*) ; 
 int /*<<< orphan*/  nvmf_host_put (int /*<<< orphan*/ ) ; 

void nvmf_free_options(struct nvmf_ctrl_options *opts)
{
	nvmf_host_put(opts->host);
	kfree(opts->transport);
	kfree(opts->traddr);
	kfree(opts->trsvcid);
	kfree(opts->subsysnqn);
	kfree(opts->host_traddr);
	kfree(opts);
}