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
typedef  int u16 ;
struct ocrdma_mcqe {int valid_ae_cmpl_cons; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ cq; } ;
struct ocrdma_dev {TYPE_2__ mq; } ;

/* Variables and functions */
 int OCRDMA_MCQE_AE_MASK ; 
 int OCRDMA_MCQE_CMPL_MASK ; 
 int /*<<< orphan*/  memset (struct ocrdma_mcqe*,int /*<<< orphan*/ ,int) ; 
 struct ocrdma_mcqe* ocrdma_get_mcqe (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_le32_to_cpu (struct ocrdma_mcqe*,int) ; 
 int /*<<< orphan*/  ocrdma_mcq_inc_tail (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_process_acqe (struct ocrdma_dev*,struct ocrdma_mcqe*) ; 
 int /*<<< orphan*/  ocrdma_process_mcqe (struct ocrdma_dev*,struct ocrdma_mcqe*) ; 
 int /*<<< orphan*/  ocrdma_ring_cq_db (struct ocrdma_dev*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int ocrdma_mq_cq_handler(struct ocrdma_dev *dev, u16 cq_id)
{
	u16 cqe_popped = 0;
	struct ocrdma_mcqe *cqe;

	while (1) {
		cqe = ocrdma_get_mcqe(dev);
		if (cqe == NULL)
			break;
		ocrdma_le32_to_cpu(cqe, sizeof(*cqe));
		cqe_popped += 1;
		if (cqe->valid_ae_cmpl_cons & OCRDMA_MCQE_AE_MASK)
			ocrdma_process_acqe(dev, cqe);
		else if (cqe->valid_ae_cmpl_cons & OCRDMA_MCQE_CMPL_MASK)
			ocrdma_process_mcqe(dev, cqe);
		memset(cqe, 0, sizeof(struct ocrdma_mcqe));
		ocrdma_mcq_inc_tail(dev);
	}
	ocrdma_ring_cq_db(dev, dev->mq.cq.id, true, false, cqe_popped);
	return 0;
}