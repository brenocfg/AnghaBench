#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hfi1_vnic_vport_info {int num_tx_q; TYPE_1__* dd; struct hfi1_vnic_sdma* sdma; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_head; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; scalar_t__ num_desc; } ;
struct hfi1_vnic_sdma {int q_idx; TYPE_4__ wait; TYPE_3__ stx; TYPE_2__* sde; int /*<<< orphan*/  state; struct hfi1_vnic_vport_info* vinfo; TYPE_1__* dd; } ;
struct TYPE_6__ {scalar_t__ descq_cnt; } ;
struct TYPE_5__ {TYPE_2__* per_sdma; } ;

/* Variables and functions */
 scalar_t__ HFI1_VNIC_SDMA_DESC_WTRMRK ; 
 int /*<<< orphan*/  HFI1_VNIC_SDMA_Q_ACTIVE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_vnic_sdma_sleep ; 
 int /*<<< orphan*/  hfi1_vnic_sdma_wakeup ; 
 int /*<<< orphan*/  iowait_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void hfi1_vnic_sdma_init(struct hfi1_vnic_vport_info *vinfo)
{
	int i;

	for (i = 0; i < vinfo->num_tx_q; i++) {
		struct hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[i];

		iowait_init(&vnic_sdma->wait, 0, NULL, hfi1_vnic_sdma_sleep,
			    hfi1_vnic_sdma_wakeup, NULL);
		vnic_sdma->sde = &vinfo->dd->per_sdma[i];
		vnic_sdma->dd = vinfo->dd;
		vnic_sdma->vinfo = vinfo;
		vnic_sdma->q_idx = i;
		vnic_sdma->state = HFI1_VNIC_SDMA_Q_ACTIVE;

		/* Add a free descriptor watermark for wakeups */
		if (vnic_sdma->sde->descq_cnt > HFI1_VNIC_SDMA_DESC_WTRMRK) {
			INIT_LIST_HEAD(&vnic_sdma->stx.list);
			vnic_sdma->stx.num_desc = HFI1_VNIC_SDMA_DESC_WTRMRK;
			list_add_tail(&vnic_sdma->stx.list,
				      &vnic_sdma->wait.tx_head);
		}
	}
}