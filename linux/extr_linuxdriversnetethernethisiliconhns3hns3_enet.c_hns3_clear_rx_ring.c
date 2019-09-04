#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sw_err_cnt; } ;
struct hns3_enet_ring {size_t next_to_use; size_t next_to_clean; TYPE_4__* tqp; int /*<<< orphan*/  syncp; TYPE_1__ stats; TYPE_5__* desc_cb; } ;
struct hns3_desc_cb {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  reuse_flag; } ;
struct TYPE_9__ {TYPE_3__* handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  netdev; } ;
struct TYPE_8__ {TYPE_2__ kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_replace_buffer (struct hns3_enet_ring*,size_t,struct hns3_desc_cb*) ; 
 int hns3_reserve_buffer_map (struct hns3_enet_ring*,struct hns3_desc_cb*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  next_to_use ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hns3_enet_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns3_clear_rx_ring(struct hns3_enet_ring *ring)
{
	struct hns3_desc_cb res_cbs;
	int ret;

	while (ring->next_to_use != ring->next_to_clean) {
		/* When a buffer is not reused, it's memory has been
		 * freed in hns3_handle_rx_bd or will be freed by
		 * stack, so we need to replace the buffer here.
		 */
		if (!ring->desc_cb[ring->next_to_use].reuse_flag) {
			ret = hns3_reserve_buffer_map(ring, &res_cbs);
			if (ret) {
				u64_stats_update_begin(&ring->syncp);
				ring->stats.sw_err_cnt++;
				u64_stats_update_end(&ring->syncp);
				/* if alloc new buffer fail, exit directly
				 * and reclear in up flow.
				 */
				netdev_warn(ring->tqp->handle->kinfo.netdev,
					    "reserve buffer map failed, ret = %d\n",
					    ret);
				return ret;
			}
			hns3_replace_buffer(ring, ring->next_to_use,
					    &res_cbs);
		}
		ring_ptr_move_fw(ring, next_to_use);
	}

	return 0;
}