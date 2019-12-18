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
typedef  void u8 ;
struct iwl_mvm {int dummy; } ;
struct iwl_fw_channel_info_v1 {int dummy; } ;
struct iwl_fw_channel_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ iwl_mvm_has_ultra_hb_channel (struct iwl_mvm*) ; 

__attribute__((used)) static inline void *iwl_mvm_chan_info_cmd_tail(struct iwl_mvm *mvm,
					       struct iwl_fw_channel_info *ci)
{
	return (u8 *)ci + (iwl_mvm_has_ultra_hb_channel(mvm) ?
			   sizeof(struct iwl_fw_channel_info) :
			   sizeof(struct iwl_fw_channel_info_v1));
}