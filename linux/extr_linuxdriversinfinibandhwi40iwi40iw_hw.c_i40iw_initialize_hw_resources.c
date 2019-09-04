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
typedef  int u32 ;
struct i40iw_qp {int dummy; } ;
struct TYPE_6__ {TYPE_2__* hmc_info; } ;
struct i40iw_device {int max_cqe; int max_qp; int max_mr; int max_cq; unsigned long max_pd; int arp_table_size; int device_cap_flags; int mr_stagmask; int /*<<< orphan*/  qptable_lock; int /*<<< orphan*/  resource_lock; int /*<<< orphan*/ * allocated_pds; int /*<<< orphan*/ * allocated_cqs; int /*<<< orphan*/ * allocated_qps; int /*<<< orphan*/ * allocated_arps; int /*<<< orphan*/ * allocated_mrs; struct i40iw_qp** qp_table; void* mem_resources; struct i40iw_arp_entry* arp_table; TYPE_3__ sc_dev; } ;
struct i40iw_arp_entry {int dummy; } ;
struct TYPE_5__ {TYPE_1__* hmc_obj; } ;
struct TYPE_4__ {int cnt; } ;

/* Variables and functions */
 size_t BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t I40IW_HMC_IW_ARP ; 
 size_t I40IW_HMC_IW_CQ ; 
 size_t I40IW_HMC_IW_MR ; 
 size_t I40IW_HMC_IW_QP ; 
 unsigned long I40IW_MAX_PDS ; 
 int IB_DEVICE_LOCAL_DMA_LKEY ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int IB_DEVICE_MEM_WINDOW ; 
 int /*<<< orphan*/  get_count_order (int) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

u32 i40iw_initialize_hw_resources(struct i40iw_device *iwdev)
{
	unsigned long num_pds;
	u32 resources_size;
	u32 max_mr;
	u32 max_qp;
	u32 max_cq;
	u32 arp_table_size;
	u32 mrdrvbits;
	void *resource_ptr;

	max_qp = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_QP].cnt;
	max_cq = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_CQ].cnt;
	max_mr = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_MR].cnt;
	arp_table_size = iwdev->sc_dev.hmc_info->hmc_obj[I40IW_HMC_IW_ARP].cnt;
	iwdev->max_cqe = 0xFFFFF;
	num_pds = I40IW_MAX_PDS;
	resources_size = sizeof(struct i40iw_arp_entry) * arp_table_size;
	resources_size += sizeof(unsigned long) * BITS_TO_LONGS(max_qp);
	resources_size += sizeof(unsigned long) * BITS_TO_LONGS(max_mr);
	resources_size += sizeof(unsigned long) * BITS_TO_LONGS(max_cq);
	resources_size += sizeof(unsigned long) * BITS_TO_LONGS(num_pds);
	resources_size += sizeof(unsigned long) * BITS_TO_LONGS(arp_table_size);
	resources_size += sizeof(struct i40iw_qp **) * max_qp;
	iwdev->mem_resources = kzalloc(resources_size, GFP_KERNEL);

	if (!iwdev->mem_resources)
		return -ENOMEM;

	iwdev->max_qp = max_qp;
	iwdev->max_mr = max_mr;
	iwdev->max_cq = max_cq;
	iwdev->max_pd = num_pds;
	iwdev->arp_table_size = arp_table_size;
	iwdev->arp_table = (struct i40iw_arp_entry *)iwdev->mem_resources;
	resource_ptr = iwdev->mem_resources + (sizeof(struct i40iw_arp_entry) * arp_table_size);

	iwdev->device_cap_flags = IB_DEVICE_LOCAL_DMA_LKEY |
	    IB_DEVICE_MEM_WINDOW | IB_DEVICE_MEM_MGT_EXTENSIONS;

	iwdev->allocated_qps = resource_ptr;
	iwdev->allocated_cqs = &iwdev->allocated_qps[BITS_TO_LONGS(max_qp)];
	iwdev->allocated_mrs = &iwdev->allocated_cqs[BITS_TO_LONGS(max_cq)];
	iwdev->allocated_pds = &iwdev->allocated_mrs[BITS_TO_LONGS(max_mr)];
	iwdev->allocated_arps = &iwdev->allocated_pds[BITS_TO_LONGS(num_pds)];
	iwdev->qp_table = (struct i40iw_qp **)(&iwdev->allocated_arps[BITS_TO_LONGS(arp_table_size)]);
	set_bit(0, iwdev->allocated_mrs);
	set_bit(0, iwdev->allocated_qps);
	set_bit(0, iwdev->allocated_cqs);
	set_bit(0, iwdev->allocated_pds);
	set_bit(0, iwdev->allocated_arps);

	/* Following for ILQ/IEQ */
	set_bit(1, iwdev->allocated_qps);
	set_bit(1, iwdev->allocated_cqs);
	set_bit(1, iwdev->allocated_pds);
	set_bit(2, iwdev->allocated_cqs);
	set_bit(2, iwdev->allocated_pds);

	spin_lock_init(&iwdev->resource_lock);
	spin_lock_init(&iwdev->qptable_lock);
	/* stag index mask has a minimum of 14 bits */
	mrdrvbits = 24 - max(get_count_order(iwdev->max_mr), 14);
	iwdev->mr_stagmask = ~(((1 << mrdrvbits) - 1) << (32 - mrdrvbits));
	return 0;
}