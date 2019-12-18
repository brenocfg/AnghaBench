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
struct iwl_mvm {int dummy; } ;
struct iwl_frame_release {int /*<<< orphan*/  nssn; int /*<<< orphan*/  baid; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_release_frames_from_notif (struct iwl_mvm*,struct napi_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_frame_release(struct iwl_mvm *mvm, struct napi_struct *napi,
			      struct iwl_rx_cmd_buffer *rxb, int queue)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_frame_release *release = (void *)pkt->data;

	iwl_mvm_release_frames_from_notif(mvm, napi, release->baid,
					  le16_to_cpu(release->nssn),
					  queue, 0);
}