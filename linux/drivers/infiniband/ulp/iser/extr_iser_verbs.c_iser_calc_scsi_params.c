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
typedef  scalar_t__ u32 ;
struct iser_device {TYPE_1__* ib_device; } ;
struct TYPE_4__ {scalar_t__ pi_support; struct iser_device* device; } ;
struct iser_conn {int /*<<< orphan*/  scsi_sg_tablesize; scalar_t__ pages_per_mr; TYPE_2__ ib_conn; } ;
struct ib_device_attr {int device_cap_flags; scalar_t__ max_fast_reg_page_list_len; scalar_t__ max_pi_fast_reg_page_list_len; } ;
struct TYPE_3__ {struct ib_device_attr attrs; } ;

/* Variables and functions */
 unsigned short DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int IB_DEVICE_MEM_MGT_EXTENSIONS ; 
 int IB_DEVICE_SG_GAPS_REG ; 
 unsigned short ISCSI_ISER_MAX_SG_TABLESIZE ; 
 int /*<<< orphan*/  SIZE_4K ; 
 int /*<<< orphan*/  min (unsigned short,unsigned short) ; 
 unsigned short min_t (int /*<<< orphan*/ ,unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  uint ; 

__attribute__((used)) static void
iser_calc_scsi_params(struct iser_conn *iser_conn,
		      unsigned int max_sectors)
{
	struct iser_device *device = iser_conn->ib_conn.device;
	struct ib_device_attr *attr = &device->ib_device->attrs;
	unsigned short sg_tablesize, sup_sg_tablesize;
	unsigned short reserved_mr_pages;
	u32 max_num_sg;

	/*
	 * FRs without SG_GAPS or FMRs can only map up to a (device) page per
	 * entry, but if the first entry is misaligned we'll end up using two
	 * entries (head and tail) for a single page worth data, so one
	 * additional entry is required.
	 */
	if ((attr->device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS) &&
	    (attr->device_cap_flags & IB_DEVICE_SG_GAPS_REG))
		reserved_mr_pages = 0;
	else
		reserved_mr_pages = 1;

	if (iser_conn->ib_conn.pi_support)
		max_num_sg = attr->max_pi_fast_reg_page_list_len;
	else
		max_num_sg = attr->max_fast_reg_page_list_len;

	sg_tablesize = DIV_ROUND_UP(max_sectors * 512, SIZE_4K);
	if (attr->device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS)
		sup_sg_tablesize =
			min_t(
			 uint, ISCSI_ISER_MAX_SG_TABLESIZE,
			 max_num_sg - reserved_mr_pages);
	else
		sup_sg_tablesize = ISCSI_ISER_MAX_SG_TABLESIZE;

	iser_conn->scsi_sg_tablesize = min(sg_tablesize, sup_sg_tablesize);
	iser_conn->pages_per_mr =
		iser_conn->scsi_sg_tablesize + reserved_mr_pages;
}