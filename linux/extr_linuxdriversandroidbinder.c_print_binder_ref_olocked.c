#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  weak; int /*<<< orphan*/  strong; int /*<<< orphan*/  desc; int /*<<< orphan*/  debug_id; } ;
struct binder_ref {TYPE_2__* node; int /*<<< orphan*/  death; TYPE_1__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  debug_id; scalar_t__ proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  binder_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_binder_ref_olocked(struct seq_file *m,
				     struct binder_ref *ref)
{
	binder_node_lock(ref->node);
	seq_printf(m, "  ref %d: desc %d %snode %d s %d w %d d %pK\n",
		   ref->data.debug_id, ref->data.desc,
		   ref->node->proc ? "" : "dead ",
		   ref->node->debug_id, ref->data.strong,
		   ref->data.weak, ref->death);
	binder_node_unlock(ref->node);
}