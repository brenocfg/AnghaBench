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
struct drm_dp_sideband_msg_tx {int seqno; TYPE_1__* dst; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** tx_slots; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int process_single_tx_qlock (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*,int) ; 

__attribute__((used)) static void process_single_up_tx_qlock(struct drm_dp_mst_topology_mgr *mgr,
				       struct drm_dp_sideband_msg_tx *txmsg)
{
	int ret;

	/* construct a chunk from the first msg in the tx_msg queue */
	ret = process_single_tx_qlock(mgr, txmsg, true);

	if (ret != 1)
		DRM_DEBUG_KMS("failed to send msg in q %d\n", ret);

	if (txmsg->seqno != -1) {
		WARN_ON((unsigned int)txmsg->seqno >
			ARRAY_SIZE(txmsg->dst->tx_slots));
		txmsg->dst->tx_slots[txmsg->seqno] = NULL;
	}
}