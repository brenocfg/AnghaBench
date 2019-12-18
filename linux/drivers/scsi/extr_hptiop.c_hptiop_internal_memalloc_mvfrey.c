#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mvfrey_outlist_entry {int dummy; } ;
struct mvfrey_inlist_entry {int dummy; } ;
struct TYPE_8__ {char* req_virt; int req_shifted_phy; int /*<<< orphan*/ * next; int /*<<< orphan*/ * scp; } ;
struct TYPE_9__ {int list_count; int internal_mem_size; int inlist_phy; int outlist_phy; int outlist_cptr_phy; int /*<<< orphan*/ * outlist_cptr; struct mvfrey_outlist_entry* outlist; struct mvfrey_inlist_entry* inlist; TYPE_3__ internal_req; TYPE_1__* mu; } ;
struct TYPE_10__ {TYPE_4__ mvfrey; } ;
struct hptiop_hba {scalar_t__ max_request_size; TYPE_5__ u; TYPE_2__* pcidev; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  inbound_conf_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hptiop_internal_memalloc_mvfrey(struct hptiop_hba *hba)
{
	u32 list_count = readl(&hba->u.mvfrey.mu->inbound_conf_ctl);
	char *p;
	dma_addr_t phy;

	BUG_ON(hba->max_request_size == 0);

	if (list_count == 0) {
		BUG_ON(1);
		return -1;
	}

	list_count >>= 16;

	hba->u.mvfrey.list_count = list_count;
	hba->u.mvfrey.internal_mem_size = 0x800 +
			list_count * sizeof(struct mvfrey_inlist_entry) +
			list_count * sizeof(struct mvfrey_outlist_entry) +
			sizeof(int);

	p = dma_alloc_coherent(&hba->pcidev->dev,
			hba->u.mvfrey.internal_mem_size, &phy, GFP_KERNEL);
	if (!p)
		return -1;

	hba->u.mvfrey.internal_req.req_virt = p;
	hba->u.mvfrey.internal_req.req_shifted_phy = phy >> 5;
	hba->u.mvfrey.internal_req.scp = NULL;
	hba->u.mvfrey.internal_req.next = NULL;

	p += 0x800;
	phy += 0x800;

	hba->u.mvfrey.inlist = (struct mvfrey_inlist_entry *)p;
	hba->u.mvfrey.inlist_phy = phy;

	p += list_count * sizeof(struct mvfrey_inlist_entry);
	phy += list_count * sizeof(struct mvfrey_inlist_entry);

	hba->u.mvfrey.outlist = (struct mvfrey_outlist_entry *)p;
	hba->u.mvfrey.outlist_phy = phy;

	p += list_count * sizeof(struct mvfrey_outlist_entry);
	phy += list_count * sizeof(struct mvfrey_outlist_entry);

	hba->u.mvfrey.outlist_cptr = (__le32 *)p;
	hba->u.mvfrey.outlist_cptr_phy = phy;

	return 0;
}