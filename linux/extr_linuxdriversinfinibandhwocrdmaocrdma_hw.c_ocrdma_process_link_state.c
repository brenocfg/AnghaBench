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
struct ocrdma_dev {int flags; } ;
struct ocrdma_ae_mcqe {int dummy; } ;
struct ocrdma_ae_lnkst_mcqe {int /*<<< orphan*/  speed_state_ptn; } ;

/* Variables and functions */
 int OCRDMA_AE_LSC_LLINK_MASK ; 
 int OCRDMA_FLAGS_LINK_STATUS_INIT ; 
 int OCRDMA_LINK_ST_MASK ; 
 int ocrdma_get_ae_link_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_update_link_state (struct ocrdma_dev*,int) ; 

__attribute__((used)) static void ocrdma_process_link_state(struct ocrdma_dev *dev,
				      struct ocrdma_ae_mcqe *cqe)
{
	struct ocrdma_ae_lnkst_mcqe *evt;
	u8 lstate;

	evt = (struct ocrdma_ae_lnkst_mcqe *)cqe;
	lstate = ocrdma_get_ae_link_state(evt->speed_state_ptn);

	if (!(lstate & OCRDMA_AE_LSC_LLINK_MASK))
		return;

	if (dev->flags & OCRDMA_FLAGS_LINK_STATUS_INIT)
		ocrdma_update_link_state(dev, (lstate & OCRDMA_LINK_ST_MASK));
}