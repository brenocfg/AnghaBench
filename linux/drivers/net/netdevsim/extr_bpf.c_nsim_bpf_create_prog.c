#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nsim_dev {int /*<<< orphan*/  bpf_bound_progs; int /*<<< orphan*/  ddir_bpf_bound_progs; int /*<<< orphan*/  prog_id_gen; } ;
struct nsim_bpf_bound_prog {char* state; int /*<<< orphan*/  l; int /*<<< orphan*/  is_loaded; int /*<<< orphan*/  ddir; struct bpf_prog* prog; struct nsim_dev* nsim_dev; } ;
struct bpf_prog {TYPE_2__* aux; } ;
struct TYPE_4__ {TYPE_1__* offload; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct nsim_bpf_bound_prog* dev_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nsim_bpf_bound_prog*) ; 
 struct nsim_bpf_bound_prog* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsim_bpf_string_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsim_bpf_create_prog(struct nsim_dev *nsim_dev,
				struct bpf_prog *prog)
{
	struct nsim_bpf_bound_prog *state;
	char name[16];

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	state->nsim_dev = nsim_dev;
	state->prog = prog;
	state->state = "verify";

	/* Program id is not populated yet when we create the state. */
	sprintf(name, "%u", nsim_dev->prog_id_gen++);
	state->ddir = debugfs_create_dir(name, nsim_dev->ddir_bpf_bound_progs);
	if (IS_ERR_OR_NULL(state->ddir)) {
		kfree(state);
		return -ENOMEM;
	}

	debugfs_create_u32("id", 0400, state->ddir, &prog->aux->id);
	debugfs_create_file("state", 0400, state->ddir,
			    &state->state, &nsim_bpf_string_fops);
	debugfs_create_bool("loaded", 0400, state->ddir, &state->is_loaded);

	list_add_tail(&state->l, &nsim_dev->bpf_bound_progs);

	prog->aux->offload->dev_priv = state;

	return 0;
}