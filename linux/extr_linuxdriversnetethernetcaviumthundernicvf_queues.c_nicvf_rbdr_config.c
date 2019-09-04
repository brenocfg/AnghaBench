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
typedef  scalar_t__ u64 ;
struct rbdr_cfg {int ena; int lines; scalar_t__ avg_con; int /*<<< orphan*/  qsize; scalar_t__ ldwb; scalar_t__ reset; } ;
struct TYPE_2__ {scalar_t__ phys_base; } ;
struct rbdr {int dma_size; scalar_t__ thresh; TYPE_1__ dmem; } ;
struct queue_set {scalar_t__ rbdr_len; struct rbdr* rbdr; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_BASE ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_CFG ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_DOOR ; 
 int /*<<< orphan*/  NIC_QSET_RBDR_0_1_THRESH ; 
 int /*<<< orphan*/  RBDR_SIZE ; 
 int /*<<< orphan*/  memset (struct rbdr_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  nicvf_reclaim_rbdr (struct nicvf*,struct rbdr*,int) ; 

__attribute__((used)) static void nicvf_rbdr_config(struct nicvf *nic, struct queue_set *qs,
			      int qidx, bool enable)
{
	struct rbdr *rbdr;
	struct rbdr_cfg rbdr_cfg;

	rbdr = &qs->rbdr[qidx];
	nicvf_reclaim_rbdr(nic, rbdr, qidx);
	if (!enable)
		return;

	/* Set descriptor base address */
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_BASE,
			      qidx, (u64)(rbdr->dmem.phys_base));

	/* Enable RBDR  & set queue size */
	/* Buffer size should be in multiples of 128 bytes */
	memset(&rbdr_cfg, 0, sizeof(struct rbdr_cfg));
	rbdr_cfg.ena = 1;
	rbdr_cfg.reset = 0;
	rbdr_cfg.ldwb = 0;
	rbdr_cfg.qsize = RBDR_SIZE;
	rbdr_cfg.avg_con = 0;
	rbdr_cfg.lines = rbdr->dma_size / 128;
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_CFG,
			      qidx, *(u64 *)&rbdr_cfg);

	/* Notify HW */
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_DOOR,
			      qidx, qs->rbdr_len - 1);

	/* Set threshold value for interrupt generation */
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_THRESH,
			      qidx, rbdr->thresh - 1);
}