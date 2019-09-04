#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* q_depth; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {void* q_depth; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {scalar_t__ i2htok; } ;
struct TYPE_17__ {TYPE_1__ mtag; } ;
struct bfi_msgq_cfg_req {TYPE_6__ rspq; TYPE_3__ cmdq; TYPE_8__ mh; } ;
struct TYPE_18__ {int /*<<< orphan*/ * msg; } ;
struct TYPE_14__ {int /*<<< orphan*/  pa; } ;
struct TYPE_16__ {int /*<<< orphan*/  depth; TYPE_5__ addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  pa; } ;
struct TYPE_13__ {int /*<<< orphan*/  depth; TYPE_2__ addr; } ;
struct bfa_msgq {TYPE_9__ init_mb; int /*<<< orphan*/  ioc; TYPE_7__ rspq; TYPE_4__ cmdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_MSGQ ; 
 int /*<<< orphan*/  BFI_MSGQ_H2I_INIT_REQ ; 
 int /*<<< orphan*/  bfa_dma_be_addr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfi_h2i_set (TYPE_8__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bfi_msgq_cfg_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_msgq_init(void *arg)
{
	struct bfa_msgq *msgq = (struct bfa_msgq *)arg;
	struct bfi_msgq_cfg_req *msgq_cfg =
		(struct bfi_msgq_cfg_req *)&msgq->init_mb.msg[0];

	memset(msgq_cfg, 0, sizeof(struct bfi_msgq_cfg_req));
	bfi_h2i_set(msgq_cfg->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_INIT_REQ, 0);
	msgq_cfg->mh.mtag.i2htok = 0;

	bfa_dma_be_addr_set(msgq_cfg->cmdq.addr, msgq->cmdq.addr.pa);
	msgq_cfg->cmdq.q_depth = htons(msgq->cmdq.depth);
	bfa_dma_be_addr_set(msgq_cfg->rspq.addr, msgq->rspq.addr.pa);
	msgq_cfg->rspq.q_depth = htons(msgq->rspq.depth);

	bfa_nw_ioc_mbox_queue(msgq->ioc, &msgq->init_mb, NULL, NULL);
}