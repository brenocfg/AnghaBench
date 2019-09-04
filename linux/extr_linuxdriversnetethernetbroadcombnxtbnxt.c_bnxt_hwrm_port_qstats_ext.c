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
struct rx_port_stats_ext {int dummy; } ;
struct hwrm_port_qstats_ext_input {int /*<<< orphan*/  rx_stat_host_addr; void* rx_stat_size; void* port_id; int /*<<< orphan*/  member_0; } ;
struct bnxt_pf_info {int port_id; } ;
struct bnxt {int flags; int /*<<< orphan*/  hw_rx_port_stats_ext_map; struct bnxt_pf_info pf; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_FLAG_PORT_STATS_EXT ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PORT_QSTATS_EXT ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_port_qstats_ext_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_port_qstats_ext_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_port_qstats_ext(struct bnxt *bp)
{
	struct hwrm_port_qstats_ext_input req = {0};
	struct bnxt_pf_info *pf = &bp->pf;

	if (!(bp->flags & BNXT_FLAG_PORT_STATS_EXT))
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_QSTATS_EXT, -1, -1);
	req.port_id = cpu_to_le16(pf->port_id);
	req.rx_stat_size = cpu_to_le16(sizeof(struct rx_port_stats_ext));
	req.rx_stat_host_addr = cpu_to_le64(bp->hw_rx_port_stats_ext_map);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}