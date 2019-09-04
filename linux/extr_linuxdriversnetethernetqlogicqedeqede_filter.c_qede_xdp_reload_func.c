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
struct TYPE_2__ {int /*<<< orphan*/  new_prog; } ;
struct qede_reload_args {TYPE_1__ u; } ;
struct qede_dev {int /*<<< orphan*/  xdp_prog; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 struct bpf_prog* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qede_xdp_reload_func(struct qede_dev *edev,
				 struct qede_reload_args *args)
{
	struct bpf_prog *old;

	old = xchg(&edev->xdp_prog, args->u.new_prog);
	if (old)
		bpf_prog_put(old);
}