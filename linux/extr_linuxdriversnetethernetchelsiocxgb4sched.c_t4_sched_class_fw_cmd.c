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
struct sched_table {struct sched_class* tab; } ;
struct sched_class {int /*<<< orphan*/  idx; } ;
struct port_info {struct sched_table* sched_tbl; struct adapter* adapter; } ;
struct TYPE_3__ {size_t class; int /*<<< orphan*/  pktsize; int /*<<< orphan*/  weight; int /*<<< orphan*/  maxrate; int /*<<< orphan*/  minrate; int /*<<< orphan*/  channel; int /*<<< orphan*/  ratemode; int /*<<< orphan*/  rateunit; int /*<<< orphan*/  mode; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct ch_sched_params {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct adapter {int dummy; } ;
typedef  enum sched_fw_ops { ____Placeholder_sched_fw_ops } sched_fw_ops ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  SCHED_FW_OP_ADD 128 
 int t4_sched_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t4_sched_class_fw_cmd(struct port_info *pi,
				 struct ch_sched_params *p,
				 enum sched_fw_ops op)
{
	struct adapter *adap = pi->adapter;
	struct sched_table *s = pi->sched_tbl;
	struct sched_class *e;
	int err = 0;

	e = &s->tab[p->u.params.class];
	switch (op) {
	case SCHED_FW_OP_ADD:
		err = t4_sched_params(adap, p->type,
				      p->u.params.level, p->u.params.mode,
				      p->u.params.rateunit,
				      p->u.params.ratemode,
				      p->u.params.channel, e->idx,
				      p->u.params.minrate, p->u.params.maxrate,
				      p->u.params.weight, p->u.params.pktsize);
		break;
	default:
		err = -ENOTSUPP;
		break;
	}

	return err;
}