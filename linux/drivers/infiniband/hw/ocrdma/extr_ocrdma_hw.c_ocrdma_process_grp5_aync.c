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
struct ocrdma_dev {int pvid; int /*<<< orphan*/  update_sl; } ;
struct ocrdma_ae_pvid_mcqe {int tag_enabled; } ;
struct ocrdma_ae_mcqe {int valid_ae_event; } ;

/* Variables and functions */
 int OCRDMA_AE_MCQE_EVENT_TYPE_MASK ; 
 int OCRDMA_AE_MCQE_EVENT_TYPE_SHIFT ; 
 int OCRDMA_AE_PVID_MCQE_ENABLED_MASK ; 
 int OCRDMA_AE_PVID_MCQE_ENABLED_SHIFT ; 
 int OCRDMA_AE_PVID_MCQE_TAG_MASK ; 
 int OCRDMA_AE_PVID_MCQE_TAG_SHIFT ; 
#define  OCRDMA_ASYNC_EVENT_COS_VALUE 129 
#define  OCRDMA_ASYNC_EVENT_PVID_STATE 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ocrdma_process_grp5_aync(struct ocrdma_dev *dev,
					struct ocrdma_ae_mcqe *cqe)
{
	struct ocrdma_ae_pvid_mcqe *evt;
	int type = (cqe->valid_ae_event & OCRDMA_AE_MCQE_EVENT_TYPE_MASK) >>
			OCRDMA_AE_MCQE_EVENT_TYPE_SHIFT;

	switch (type) {
	case OCRDMA_ASYNC_EVENT_PVID_STATE:
		evt = (struct ocrdma_ae_pvid_mcqe *)cqe;
		if ((evt->tag_enabled & OCRDMA_AE_PVID_MCQE_ENABLED_MASK) >>
			OCRDMA_AE_PVID_MCQE_ENABLED_SHIFT)
			dev->pvid = ((evt->tag_enabled &
					OCRDMA_AE_PVID_MCQE_TAG_MASK) >>
					OCRDMA_AE_PVID_MCQE_TAG_SHIFT);
		break;

	case OCRDMA_ASYNC_EVENT_COS_VALUE:
		atomic_set(&dev->update_sl, 1);
		break;
	default:
		/* Not interested evts. */
		break;
	}
}