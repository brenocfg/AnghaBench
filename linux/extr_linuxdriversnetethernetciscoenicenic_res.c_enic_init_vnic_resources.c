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
struct TYPE_2__ {int /*<<< orphan*/  intr_timer_type; int /*<<< orphan*/  intr_timer_usec; } ;
struct enic {int intr_count; unsigned int rq_count; unsigned int wq_count; unsigned int cq_count; TYPE_1__ config; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * wq; int /*<<< orphan*/ * rq; int /*<<< orphan*/  vdev; } ;
typedef  enum vnic_dev_intr_mode { ____Placeholder_vnic_dev_intr_mode } vnic_dev_intr_mode ;

/* Variables and functions */
#define  VNIC_DEV_INTR_MODE_INTX 130 
#define  VNIC_DEV_INTR_MODE_MSI 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int /*<<< orphan*/  vnic_cq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vnic_rq_init (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vnic_wq_init (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 

void enic_init_vnic_resources(struct enic *enic)
{
	enum vnic_dev_intr_mode intr_mode;
	unsigned int mask_on_assertion;
	unsigned int interrupt_offset;
	unsigned int error_interrupt_enable;
	unsigned int error_interrupt_offset;
	unsigned int cq_index;
	unsigned int i;

	intr_mode = vnic_dev_get_intr_mode(enic->vdev);

	/* Init RQ/WQ resources.
	 *
	 * RQ[0 - n-1] point to CQ[0 - n-1]
	 * WQ[0 - m-1] point to CQ[n - n+m-1]
	 *
	 * Error interrupt is not enabled for MSI.
	 */

	switch (intr_mode) {
	case VNIC_DEV_INTR_MODE_INTX:
	case VNIC_DEV_INTR_MODE_MSIX:
		error_interrupt_enable = 1;
		error_interrupt_offset = enic->intr_count - 2;
		break;
	default:
		error_interrupt_enable = 0;
		error_interrupt_offset = 0;
		break;
	}

	for (i = 0; i < enic->rq_count; i++) {
		cq_index = i;
		vnic_rq_init(&enic->rq[i],
			cq_index,
			error_interrupt_enable,
			error_interrupt_offset);
	}

	for (i = 0; i < enic->wq_count; i++) {
		cq_index = enic->rq_count + i;
		vnic_wq_init(&enic->wq[i],
			cq_index,
			error_interrupt_enable,
			error_interrupt_offset);
	}

	/* Init CQ resources
	 *
	 * CQ[0 - n+m-1] point to INTR[0] for INTx, MSI
	 * CQ[0 - n+m-1] point to INTR[0 - n+m-1] for MSI-X
	 */

	for (i = 0; i < enic->cq_count; i++) {

		switch (intr_mode) {
		case VNIC_DEV_INTR_MODE_MSIX:
			interrupt_offset = i;
			break;
		default:
			interrupt_offset = 0;
			break;
		}

		vnic_cq_init(&enic->cq[i],
			0 /* flow_control_enable */,
			1 /* color_enable */,
			0 /* cq_head */,
			0 /* cq_tail */,
			1 /* cq_tail_color */,
			1 /* interrupt_enable */,
			1 /* cq_entry_enable */,
			0 /* cq_message_enable */,
			interrupt_offset,
			0 /* cq_message_addr */);
	}

	/* Init INTR resources
	 *
	 * mask_on_assertion is not used for INTx due to the level-
	 * triggered nature of INTx
	 */

	switch (intr_mode) {
	case VNIC_DEV_INTR_MODE_MSI:
	case VNIC_DEV_INTR_MODE_MSIX:
		mask_on_assertion = 1;
		break;
	default:
		mask_on_assertion = 0;
		break;
	}

	for (i = 0; i < enic->intr_count; i++) {
		vnic_intr_init(&enic->intr[i],
			enic->config.intr_timer_usec,
			enic->config.intr_timer_type,
			mask_on_assertion);
	}
}