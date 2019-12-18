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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct iwl_fw_channel_info_v1 {void* ctrl_pos; void* width; void* band; int /*<<< orphan*/  channel; } ;
struct iwl_fw_channel_info {void* ctrl_pos; void* width; void* band; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_ultra_hb_channel (struct iwl_mvm*) ; 

__attribute__((used)) static inline void iwl_mvm_set_chan_info(struct iwl_mvm *mvm,
					 struct iwl_fw_channel_info *ci,
					 u32 chan, u8 band, u8 width,
					 u8 ctrl_pos)
{
	if (iwl_mvm_has_ultra_hb_channel(mvm)) {
		ci->channel = cpu_to_le32(chan);
		ci->band = band;
		ci->width = width;
		ci->ctrl_pos = ctrl_pos;
	} else {
		struct iwl_fw_channel_info_v1 *ci_v1 =
					(struct iwl_fw_channel_info_v1 *)ci;

		ci_v1->channel = chan;
		ci_v1->band = band;
		ci_v1->width = width;
		ci_v1->ctrl_pos = ctrl_pos;
	}
}