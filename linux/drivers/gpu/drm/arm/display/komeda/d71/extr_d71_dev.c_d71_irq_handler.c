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
typedef  int u32 ;
struct komeda_events {int /*<<< orphan*/ * pipes; int /*<<< orphan*/  global; } ;
struct komeda_dev {struct d71_dev* chip_data; } ;
struct d71_dev {int /*<<< orphan*/ * pipes; int /*<<< orphan*/  gcu_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_IRQ_CLEAR ; 
 int /*<<< orphan*/  BLK_IRQ_RAW_STATUS ; 
 int /*<<< orphan*/  BLK_STATUS ; 
 int GCU_IRQ_CVAL0 ; 
 int GCU_IRQ_CVAL1 ; 
 int GCU_IRQ_ERR ; 
 int GCU_STATUS_MERR ; 
 int /*<<< orphan*/  GLB_IRQ_STATUS ; 
 int GLB_IRQ_STATUS_GCU ; 
 int GLB_IRQ_STATUS_PIPE0 ; 
 int GLB_IRQ_STATUS_PIPE1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KOMEDA_ERR_MERR ; 
 int /*<<< orphan*/  KOMEDA_EVENT_FLIP ; 
 int /*<<< orphan*/  get_pipeline_event (int /*<<< orphan*/ ,int) ; 
 int malidp_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  malidp_write32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
d71_irq_handler(struct komeda_dev *mdev, struct komeda_events *evts)
{
	struct d71_dev *d71 = mdev->chip_data;
	u32 status, gcu_status, raw_status;

	gcu_status = malidp_read32(d71->gcu_addr, GLB_IRQ_STATUS);

	if (gcu_status & GLB_IRQ_STATUS_GCU) {
		raw_status = malidp_read32(d71->gcu_addr, BLK_IRQ_RAW_STATUS);
		if (raw_status & GCU_IRQ_CVAL0)
			evts->pipes[0] |= KOMEDA_EVENT_FLIP;
		if (raw_status & GCU_IRQ_CVAL1)
			evts->pipes[1] |= KOMEDA_EVENT_FLIP;
		if (raw_status & GCU_IRQ_ERR) {
			status = malidp_read32(d71->gcu_addr, BLK_STATUS);
			if (status & GCU_STATUS_MERR) {
				evts->global |= KOMEDA_ERR_MERR;
				malidp_write32_mask(d71->gcu_addr, BLK_STATUS,
						    GCU_STATUS_MERR, 0);
			}
		}

		malidp_write32(d71->gcu_addr, BLK_IRQ_CLEAR, raw_status);
	}

	if (gcu_status & GLB_IRQ_STATUS_PIPE0)
		evts->pipes[0] |= get_pipeline_event(d71->pipes[0], gcu_status);

	if (gcu_status & GLB_IRQ_STATUS_PIPE1)
		evts->pipes[1] |= get_pipeline_event(d71->pipes[1], gcu_status);

	return gcu_status ? IRQ_HANDLED : IRQ_NONE;
}