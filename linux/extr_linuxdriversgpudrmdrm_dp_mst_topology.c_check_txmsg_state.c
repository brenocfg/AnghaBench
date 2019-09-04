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
struct drm_dp_sideband_msg_tx {int /*<<< orphan*/  state; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;

/* Variables and functions */
 unsigned int DRM_DP_SIDEBAND_TX_RX ; 
 unsigned int DRM_DP_SIDEBAND_TX_TIMEOUT ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_txmsg_state(struct drm_dp_mst_topology_mgr *mgr,
			      struct drm_dp_sideband_msg_tx *txmsg)
{
	unsigned int state;

	/*
	 * All updates to txmsg->state are protected by mgr->qlock, and the two
	 * cases we check here are terminal states. For those the barriers
	 * provided by the wake_up/wait_event pair are enough.
	 */
	state = READ_ONCE(txmsg->state);
	return (state == DRM_DP_SIDEBAND_TX_RX ||
		state == DRM_DP_SIDEBAND_TX_TIMEOUT);
}