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
typedef  int /*<<< orphan*/  uint8_t ;
struct fw_fcoe_stats_cmd {int /*<<< orphan*/  free_to_len16; } ;
struct fw_fcoe_port_stats {int /*<<< orphan*/  rx_err_frames; int /*<<< orphan*/  rx_ucast_frames; int /*<<< orphan*/  rx_ucast_bytes; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_bcast_frames; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_pf_frames; int /*<<< orphan*/  rx_pf_bytes; int /*<<< orphan*/  tx_offload_frames; int /*<<< orphan*/  tx_offload_bytes; int /*<<< orphan*/  tx_drop_frames; int /*<<< orphan*/  tx_ucast_frames; int /*<<< orphan*/  tx_ucast_bytes; int /*<<< orphan*/  tx_mcast_frames; int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_bcast_frames; int /*<<< orphan*/  tx_bcast_bytes; } ;
struct fw_fcoe_port_cmd_params {int idx; int nstats; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;

/* Variables and functions */
 int CSIO_STATS_OFFSET ; 
 int FW_CMD_RETVAL_G (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct fw_fcoe_port_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void
csio_mb_process_portparams_rsp(struct csio_hw *hw,
				struct csio_mb *mbp,
				enum fw_retval *retval,
				struct fw_fcoe_port_cmd_params *portparams,
				struct fw_fcoe_port_stats *portstats)
{
	struct fw_fcoe_stats_cmd *rsp = (struct fw_fcoe_stats_cmd *)(mbp->mb);
	struct fw_fcoe_port_stats stats;
	uint8_t *src;
	uint8_t *dst;

	*retval = FW_CMD_RETVAL_G(ntohl(rsp->free_to_len16));

	memset(&stats, 0, sizeof(struct fw_fcoe_port_stats));

	if (*retval == FW_SUCCESS) {
		dst = (uint8_t *)(&stats) + ((portparams->idx - 1) * 8);
		src = (uint8_t *)rsp + (CSIO_STATS_OFFSET * 8);
		memcpy(dst, src, (portparams->nstats * 8));
		if (portparams->idx == 1) {
			/* Get the first 6 flits from the Mailbox */
			portstats->tx_bcast_bytes = stats.tx_bcast_bytes;
			portstats->tx_bcast_frames = stats.tx_bcast_frames;
			portstats->tx_mcast_bytes = stats.tx_mcast_bytes;
			portstats->tx_mcast_frames = stats.tx_mcast_frames;
			portstats->tx_ucast_bytes = stats.tx_ucast_bytes;
			portstats->tx_ucast_frames = stats.tx_ucast_frames;
		}
		if (portparams->idx == 7) {
			/* Get the second 6 flits from the Mailbox */
			portstats->tx_drop_frames = stats.tx_drop_frames;
			portstats->tx_offload_bytes = stats.tx_offload_bytes;
			portstats->tx_offload_frames = stats.tx_offload_frames;
#if 0
			portstats->rx_pf_bytes = stats.rx_pf_bytes;
			portstats->rx_pf_frames	= stats.rx_pf_frames;
#endif
			portstats->rx_bcast_bytes = stats.rx_bcast_bytes;
			portstats->rx_bcast_frames = stats.rx_bcast_frames;
			portstats->rx_mcast_bytes = stats.rx_mcast_bytes;
		}
		if (portparams->idx == 13) {
			/* Get the last 4 flits from the Mailbox */
			portstats->rx_mcast_frames = stats.rx_mcast_frames;
			portstats->rx_ucast_bytes = stats.rx_ucast_bytes;
			portstats->rx_ucast_frames = stats.rx_ucast_frames;
			portstats->rx_err_frames = stats.rx_err_frames;
		}
	}
}