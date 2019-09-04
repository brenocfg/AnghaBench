#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct axi_dmac_sg {scalar_t__ id; int schedule_when_free; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; } ;
struct axi_dmac_desc {size_t num_completed; size_t num_sgs; TYPE_1__ vdesc; scalar_t__ cyclic; struct axi_dmac_sg* sg; } ;
struct axi_dmac_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ AXI_DMAC_SG_UNUSED ; 
 unsigned int BIT (scalar_t__) ; 
 struct axi_dmac_desc* axi_dmac_active_desc (struct axi_dmac_chan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_1__*) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (TYPE_1__*) ; 

__attribute__((used)) static bool axi_dmac_transfer_done(struct axi_dmac_chan *chan,
	unsigned int completed_transfers)
{
	struct axi_dmac_desc *active;
	struct axi_dmac_sg *sg;
	bool start_next = false;

	active = axi_dmac_active_desc(chan);
	if (!active)
		return false;

	do {
		sg = &active->sg[active->num_completed];
		if (sg->id == AXI_DMAC_SG_UNUSED) /* Not yet submitted */
			break;
		if (!(BIT(sg->id) & completed_transfers))
			break;
		active->num_completed++;
		sg->id = AXI_DMAC_SG_UNUSED;
		if (sg->schedule_when_free) {
			sg->schedule_when_free = false;
			start_next = true;
		}

		if (active->cyclic)
			vchan_cyclic_callback(&active->vdesc);

		if (active->num_completed == active->num_sgs) {
			if (active->cyclic) {
				active->num_completed = 0; /* wrap around */
			} else {
				list_del(&active->vdesc.node);
				vchan_cookie_complete(&active->vdesc);
				active = axi_dmac_active_desc(chan);
			}
		}
	} while (active);

	return start_next;
}