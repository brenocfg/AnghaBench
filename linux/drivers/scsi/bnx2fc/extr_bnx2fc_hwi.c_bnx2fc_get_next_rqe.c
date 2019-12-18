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
typedef  int u8 ;
struct bnx2fc_rport {int rq_cons_idx; scalar_t__ rq; } ;

/* Variables and functions */
 int BNX2FC_RQ_BUF_SZ ; 
 int BNX2FC_RQ_WQES_MAX ; 

char *bnx2fc_get_next_rqe(struct bnx2fc_rport *tgt, u8 num_items)
{
	char *buf = (char *)tgt->rq + (tgt->rq_cons_idx * BNX2FC_RQ_BUF_SZ);

	if (tgt->rq_cons_idx + num_items > BNX2FC_RQ_WQES_MAX)
		return NULL;

	tgt->rq_cons_idx += num_items;

	if (tgt->rq_cons_idx >= BNX2FC_RQ_WQES_MAX)
		tgt->rq_cons_idx -= BNX2FC_RQ_WQES_MAX;

	return buf;
}