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
struct ulptx_idata {int dummy; } ;
struct ulp_mem_io {int dummy; } ;
struct sk_buff {scalar_t__ head; } ;
struct scatterlist {int dummy; } ;
struct cxgbi_task_tag_info {int dummy; } ;
struct cxgbi_sock {int /*<<< orphan*/  lock; int /*<<< orphan*/  port_id; int /*<<< orphan*/  tid; struct cxgbi_device* cdev; } ;
struct cxgbi_ppm {int dummy; } ;
struct cxgbi_pagepod {int dummy; } ;
struct cxgbi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SKCBF_TX_FLAG_COMPL ; 
 int /*<<< orphan*/  SKCBF_TX_MEM_WRITE ; 
 int /*<<< orphan*/  cxgbi_ddp_set_one_ppod (struct cxgbi_pagepod*,struct cxgbi_task_tag_info*,struct scatterlist**,unsigned int*) ; 
 int /*<<< orphan*/  cxgbi_skcb_set_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_skb_entail (struct cxgbi_sock*,struct sk_buff*) ; 
 struct sk_buff* ddp_ppod_init_idata (struct cxgbi_device*,struct cxgbi_ppm*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ddp_ppod_write_idata(struct cxgbi_ppm *ppm, struct cxgbi_sock *csk,
				struct cxgbi_task_tag_info *ttinfo,
				unsigned int idx, unsigned int npods,
				struct scatterlist **sg_pp,
				unsigned int *sg_off)
{
	struct cxgbi_device *cdev = csk->cdev;
	struct sk_buff *skb = ddp_ppod_init_idata(cdev, ppm, idx, npods,
						  csk->tid);
	struct ulp_mem_io *req;
	struct ulptx_idata *idata;
	struct cxgbi_pagepod *ppod;
	int i;

	if (!skb)
		return -ENOMEM;

	req = (struct ulp_mem_io *)skb->head;
	idata = (struct ulptx_idata *)(req + 1);
	ppod = (struct cxgbi_pagepod *)(idata + 1);

	for (i = 0; i < npods; i++, ppod++)
		cxgbi_ddp_set_one_ppod(ppod, ttinfo, sg_pp, sg_off);

	cxgbi_skcb_set_flag(skb, SKCBF_TX_MEM_WRITE);
	cxgbi_skcb_set_flag(skb, SKCBF_TX_FLAG_COMPL);
	set_wr_txq(skb, CPL_PRIORITY_DATA, csk->port_id);

	spin_lock_bh(&csk->lock);
	cxgbi_sock_skb_entail(csk, skb);
	spin_unlock_bh(&csk->lock);

	return 0;
}