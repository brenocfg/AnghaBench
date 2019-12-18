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
struct htt_peer_map_event {size_t peer_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  vdev_id; } ;
struct ath10k_peer {int /*<<< orphan*/  peer_ids; int /*<<< orphan*/  list; int /*<<< orphan*/  addr; int /*<<< orphan*/  vdev_id; } ;
struct ath10k_htt {struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  data_lock; struct ath10k_peer** peer_map; int /*<<< orphan*/  peer_mapping_wq; int /*<<< orphan*/  peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 size_t ATH10K_MAX_NUM_PEER_IDS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct ath10k_peer* ath10k_peer_find (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,size_t) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath10k_peer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ath10k_peer_map_event(struct ath10k_htt *htt,
			   struct htt_peer_map_event *ev)
{
	struct ath10k *ar = htt->ar;
	struct ath10k_peer *peer;

	if (ev->peer_id >= ATH10K_MAX_NUM_PEER_IDS) {
		ath10k_warn(ar,
			    "received htt peer map event with idx out of bounds: %hu\n",
			    ev->peer_id);
		return;
	}

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, ev->vdev_id, ev->addr);
	if (!peer) {
		peer = kzalloc(sizeof(*peer), GFP_ATOMIC);
		if (!peer)
			goto exit;

		peer->vdev_id = ev->vdev_id;
		ether_addr_copy(peer->addr, ev->addr);
		list_add(&peer->list, &ar->peers);
		wake_up(&ar->peer_mapping_wq);
	}

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt peer map vdev %d peer %pM id %d\n",
		   ev->vdev_id, ev->addr, ev->peer_id);

	WARN_ON(ar->peer_map[ev->peer_id] && (ar->peer_map[ev->peer_id] != peer));
	ar->peer_map[ev->peer_id] = peer;
	set_bit(ev->peer_id, peer->peer_ids);
exit:
	spin_unlock_bh(&ar->data_lock);
}