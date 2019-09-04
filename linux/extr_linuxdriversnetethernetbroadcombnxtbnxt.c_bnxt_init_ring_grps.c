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
struct bnxt_ring_grp_info {int dummy; } ;
struct bnxt {int cp_nr_rings; TYPE_1__* grp_info; } ;
struct TYPE_2__ {void* cp_fw_ring_id; void* agg_fw_ring_id; void* rx_fw_ring_id; void* fw_grp_id; void* fw_stats_ctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* INVALID_HW_RING_ID ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_init_ring_grps(struct bnxt *bp, bool irq_re_init)
{
	int i;

	if (irq_re_init) {
		bp->grp_info = kcalloc(bp->cp_nr_rings,
				       sizeof(struct bnxt_ring_grp_info),
				       GFP_KERNEL);
		if (!bp->grp_info)
			return -ENOMEM;
	}
	for (i = 0; i < bp->cp_nr_rings; i++) {
		if (irq_re_init)
			bp->grp_info[i].fw_stats_ctx = INVALID_HW_RING_ID;
		bp->grp_info[i].fw_grp_id = INVALID_HW_RING_ID;
		bp->grp_info[i].rx_fw_ring_id = INVALID_HW_RING_ID;
		bp->grp_info[i].agg_fw_ring_id = INVALID_HW_RING_ID;
		bp->grp_info[i].cp_fw_ring_id = INVALID_HW_RING_ID;
	}
	return 0;
}