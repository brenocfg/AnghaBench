#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  min_cbm_bits; } ;
struct rdt_resource {TYPE_3__ cache; } ;
struct kernfs_open_file {TYPE_2__* kn; } ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct TYPE_4__ {struct rdt_resource* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdt_min_cbm_bits_show(struct kernfs_open_file *of,
			     struct seq_file *seq, void *v)
{
	struct rdt_resource *r = of->kn->parent->priv;

	seq_printf(seq, "%u\n", r->cache.min_cbm_bits);
	return 0;
}