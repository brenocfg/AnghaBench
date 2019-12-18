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
struct ocrdma_qp {scalar_t__ rq_db; scalar_t__ sq_db; } ;
struct ocrdma_pd {int id; } ;
struct TYPE_2__ {int db_page_size; scalar_t__ db; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;

/* Variables and functions */
 scalar_t__ OCRDMA_ASIC_GEN_SKH_R ; 
 scalar_t__ OCRDMA_DB_GEN2_RQ_OFFSET ; 
 scalar_t__ OCRDMA_DB_GEN2_SQ_OFFSET ; 
 scalar_t__ OCRDMA_DB_RQ_OFFSET ; 
 scalar_t__ OCRDMA_DB_SQ_OFFSET ; 
 scalar_t__ ocrdma_get_asic_type (struct ocrdma_dev*) ; 

__attribute__((used)) static void ocrdma_set_qp_db(struct ocrdma_dev *dev, struct ocrdma_qp *qp,
			     struct ocrdma_pd *pd)
{
	if (ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R) {
		qp->sq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_GEN2_SQ_OFFSET;
		qp->rq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_GEN2_RQ_OFFSET;
	} else {
		qp->sq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_SQ_OFFSET;
		qp->rq_db = dev->nic_info.db +
			(pd->id * dev->nic_info.db_page_size) +
			OCRDMA_DB_RQ_OFFSET;
	}
}