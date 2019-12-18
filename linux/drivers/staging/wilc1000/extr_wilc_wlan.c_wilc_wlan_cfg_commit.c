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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {struct wilc* wilc; } ;
struct TYPE_2__ {char cmd_type; int seq_no; int /*<<< orphan*/  driver_handler; int /*<<< orphan*/  total_len; } ;
struct wilc_cfg_frame {TYPE_1__ hdr; } ;
struct wilc_cfg_cmd_hdr {int dummy; } ;
struct wilc {int cfg_frame_offset; int cfg_seq_no; struct wilc_cfg_frame cfg_frame; } ;

/* Variables and functions */
 int WILC_CFG_SET ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_wlan_txq_add_cfg_pkt (struct wilc_vif*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wilc_wlan_cfg_commit(struct wilc_vif *vif, int type,
				u32 drv_handler)
{
	struct wilc *wilc = vif->wilc;
	struct wilc_cfg_frame *cfg = &wilc->cfg_frame;
	int t_len = wilc->cfg_frame_offset + sizeof(struct wilc_cfg_cmd_hdr);

	if (type == WILC_CFG_SET)
		cfg->hdr.cmd_type = 'W';
	else
		cfg->hdr.cmd_type = 'Q';

	cfg->hdr.seq_no = wilc->cfg_seq_no % 256;
	cfg->hdr.total_len = cpu_to_le16(t_len);
	cfg->hdr.driver_handler = cpu_to_le32(drv_handler);
	wilc->cfg_seq_no = cfg->hdr.seq_no;

	if (!wilc_wlan_txq_add_cfg_pkt(vif, (u8 *)&cfg->hdr, t_len))
		return -1;

	return 0;
}