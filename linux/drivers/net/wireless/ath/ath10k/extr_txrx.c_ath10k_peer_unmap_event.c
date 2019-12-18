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
struct htt_peer_unmap_event {size_t peer_id; } ;
struct ath10k_peer {int /*<<< orphan*/  list; int /*<<< orphan*/  peer_ids; int /*<<< orphan*/  addr; int /*<<< orphan*/  vdev_id; } ;
struct ath10k_htt {struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  data_lock; int /*<<< orphan*/  peer_mapping_wq; int /*<<< orphan*/ ** peer_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 size_t ATH10K_MAX_NUM_PEER_IDS ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct ath10k_peer* ath10k_peer_find_by_id (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,size_t) ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ath10k_peer*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ath10k_peer_unmap_event(struct ath10k_htt *htt,
			     struct htt_peer_unmap_event *ev)
{
	struct ath10k *ar = htt->ar;
	struct ath10k_peer *peer;

	if (ev->peer_id >= ATH10K_MAX_NUM_PEER_IDS) {
		ath10k_warn(ar,
			    "received htt peer unmap event with idx out of bounds: %hu\n",
			    ev->peer_id);
		return;
	}

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, ev->peer_id);
	if (!peer) {
		ath10k_warn(ar, "peer-unmap-event: unknown peer id %d\n",
			    ev->peer_id);
		goto exit;
	}

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt peer unmap vdev %d peer %pM id %d\n",
		   peer->vdev_id, peer->addr, ev->peer_id);

	ar->peer_map[ev->peer_id] = NULL;
	clear_bit(ev->peer_id, peer->peer_ids);

	if (bitmap_empty(peer->peer_ids, ATH10K_MAX_NUM_PEER_IDS)) {
		list_del(&peer->list);
		kfree(peer);
		wake_up(&ar->peer_mapping_wq);
	}

exit:
	spin_unlock_bh(&ar->data_lock);
}