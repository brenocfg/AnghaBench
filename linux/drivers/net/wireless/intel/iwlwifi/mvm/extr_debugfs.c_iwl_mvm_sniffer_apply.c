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
struct iwl_rx_packet {int dummy; } ;
struct iwl_notif_wait_data {int dummy; } ;
struct iwl_mvm_sniffer_apply {int /*<<< orphan*/  bssid; TYPE_1__* mvm; int /*<<< orphan*/  aid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_bssid; int /*<<< orphan*/  cur_aid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool iwl_mvm_sniffer_apply(struct iwl_notif_wait_data *notif_data,
				  struct iwl_rx_packet *pkt, void *data)
{
	struct iwl_mvm_sniffer_apply *apply = data;

	apply->mvm->cur_aid = cpu_to_le16(apply->aid);
	memcpy(apply->mvm->cur_bssid, apply->bssid,
	       sizeof(apply->mvm->cur_bssid));

	return true;
}