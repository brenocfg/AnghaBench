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
struct TYPE_2__ {struct bpf_prog* new_prog; } ;
struct qede_reload_args {TYPE_1__ u; int /*<<< orphan*/ * func; } ;
struct qede_dev {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qede_reload (struct qede_dev*,struct qede_reload_args*,int) ; 
 int /*<<< orphan*/  qede_xdp_reload_func ; 

__attribute__((used)) static int qede_xdp_set(struct qede_dev *edev, struct bpf_prog *prog)
{
	struct qede_reload_args args;

	/* If we're called, there was already a bpf reference increment */
	args.func = &qede_xdp_reload_func;
	args.u.new_prog = prog;
	qede_reload(edev, &args, false);

	return 0;
}