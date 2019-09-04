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
struct rc_dev {TYPE_1__* raw; } ;
struct bpf_prog_array_item {scalar_t__ prog; } ;
struct TYPE_4__ {struct bpf_prog_array_item* items; } ;
struct TYPE_3__ {int /*<<< orphan*/  progs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_array_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (scalar_t__) ; 
 TYPE_2__* rcu_dereference (int /*<<< orphan*/ ) ; 

void lirc_bpf_free(struct rc_dev *rcdev)
{
	struct bpf_prog_array_item *item;

	if (!rcdev->raw->progs)
		return;

	item = rcu_dereference(rcdev->raw->progs)->items;
	while (item->prog) {
		bpf_prog_put(item->prog);
		item++;
	}

	bpf_prog_array_free(rcdev->raw->progs);
}