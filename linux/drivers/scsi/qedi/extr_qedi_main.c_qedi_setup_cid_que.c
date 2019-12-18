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
typedef  int u32 ;
struct TYPE_2__ {int* cid_que; int cid_q_max_idx; int cid_free_cnt; int /*<<< orphan*/ ** conn_cid_tbl; scalar_t__ cid_q_cons_idx; scalar_t__ cid_q_prod_idx; int /*<<< orphan*/ * cid_que_base; } ;
struct qedi_ctx {int max_active_conns; TYPE_1__ cid_que; } ;
struct qedi_conn {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_setup_cid_que(struct qedi_ctx *qedi)
{
	int i;

	qedi->cid_que.cid_que_base = kmalloc_array(qedi->max_active_conns,
						   sizeof(u32), GFP_KERNEL);
	if (!qedi->cid_que.cid_que_base)
		return -ENOMEM;

	qedi->cid_que.conn_cid_tbl = kmalloc_array(qedi->max_active_conns,
						   sizeof(struct qedi_conn *),
						   GFP_KERNEL);
	if (!qedi->cid_que.conn_cid_tbl) {
		kfree(qedi->cid_que.cid_que_base);
		qedi->cid_que.cid_que_base = NULL;
		return -ENOMEM;
	}

	qedi->cid_que.cid_que = (u32 *)qedi->cid_que.cid_que_base;
	qedi->cid_que.cid_q_prod_idx = 0;
	qedi->cid_que.cid_q_cons_idx = 0;
	qedi->cid_que.cid_q_max_idx = qedi->max_active_conns;
	qedi->cid_que.cid_free_cnt = qedi->max_active_conns;

	for (i = 0; i < qedi->max_active_conns; i++) {
		qedi->cid_que.cid_que[i] = i;
		qedi->cid_que.conn_cid_tbl[i] = NULL;
	}

	return 0;
}