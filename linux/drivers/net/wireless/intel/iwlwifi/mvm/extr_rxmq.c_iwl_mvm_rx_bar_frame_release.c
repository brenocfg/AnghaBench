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
struct napi_struct {int dummy; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_baid_data {unsigned int tid; unsigned int sta_id; } ;
struct iwl_mvm {int /*<<< orphan*/ * baid_map; } ;
struct iwl_bar_frame_release {int /*<<< orphan*/  sta_tid; int /*<<< orphan*/  ba_info; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWL_BAR_FRAME_RELEASE_BAID_MASK ; 
 int /*<<< orphan*/  IWL_BAR_FRAME_RELEASE_NSSN_MASK ; 
 int /*<<< orphan*/  IWL_BAR_FRAME_RELEASE_STA_MASK ; 
 int /*<<< orphan*/  IWL_BAR_FRAME_RELEASE_TID_MASK ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_mvm*,char*,unsigned int) ; 
 unsigned int IWL_RX_REORDER_DATA_INVALID_BAID ; 
 scalar_t__ WARN (int,char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_release_frames_from_notif (struct iwl_mvm*,struct napi_struct*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int le32_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_baid_data* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_bar_frame_release(struct iwl_mvm *mvm, struct napi_struct *napi,
				  struct iwl_rx_cmd_buffer *rxb, int queue)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_bar_frame_release *release = (void *)pkt->data;
	unsigned int baid = le32_get_bits(release->ba_info,
					  IWL_BAR_FRAME_RELEASE_BAID_MASK);
	unsigned int nssn = le32_get_bits(release->ba_info,
					  IWL_BAR_FRAME_RELEASE_NSSN_MASK);
	unsigned int sta_id = le32_get_bits(release->sta_tid,
					    IWL_BAR_FRAME_RELEASE_STA_MASK);
	unsigned int tid = le32_get_bits(release->sta_tid,
					 IWL_BAR_FRAME_RELEASE_TID_MASK);
	struct iwl_mvm_baid_data *baid_data;

	if (WARN_ON_ONCE(baid == IWL_RX_REORDER_DATA_INVALID_BAID ||
			 baid >= ARRAY_SIZE(mvm->baid_map)))
		return;

	rcu_read_lock();
	baid_data = rcu_dereference(mvm->baid_map[baid]);
	if (!baid_data) {
		IWL_DEBUG_RX(mvm,
			     "Got valid BAID %d but not allocated, invalid BAR release!\n",
			      baid);
		goto out;
	}

	if (WARN(tid != baid_data->tid || sta_id != baid_data->sta_id,
		 "baid 0x%x is mapped to sta:%d tid:%d, but BAR release received for sta:%d tid:%d\n",
		 baid, baid_data->sta_id, baid_data->tid, sta_id,
		 tid))
		goto out;

	iwl_mvm_release_frames_from_notif(mvm, napi, baid, nssn, queue, 0);
out:
	rcu_read_unlock();
}