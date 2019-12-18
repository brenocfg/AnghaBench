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
typedef  int u8 ;
struct rx_ring {int /*<<< orphan*/  rx_errors; } ;
struct nic_stats {int /*<<< orphan*/  rx_crc_err; int /*<<< orphan*/  rx_frame_len_err; int /*<<< orphan*/  rx_preamble_err; int /*<<< orphan*/  rx_undersize_err; int /*<<< orphan*/  rx_oversize_err; int /*<<< orphan*/  rx_code_err; int /*<<< orphan*/  rx_err_count; } ;
struct ql_adapter {struct nic_stats nic_stats; } ;

/* Variables and functions */
#define  IB_MAC_IOCB_RSP_ERR_CODE_ERR 133 
#define  IB_MAC_IOCB_RSP_ERR_CRC 132 
#define  IB_MAC_IOCB_RSP_ERR_FRAME_LEN 131 
 int IB_MAC_IOCB_RSP_ERR_MASK ; 
#define  IB_MAC_IOCB_RSP_ERR_OVERSIZE 130 
#define  IB_MAC_IOCB_RSP_ERR_PREAMBLE 129 
#define  IB_MAC_IOCB_RSP_ERR_UNDERSIZE 128 

__attribute__((used)) static void ql_categorize_rx_err(struct ql_adapter *qdev, u8 rx_err,
				 struct rx_ring *rx_ring)
{
	struct nic_stats *stats = &qdev->nic_stats;

	stats->rx_err_count++;
	rx_ring->rx_errors++;

	switch (rx_err & IB_MAC_IOCB_RSP_ERR_MASK) {
	case IB_MAC_IOCB_RSP_ERR_CODE_ERR:
		stats->rx_code_err++;
		break;
	case IB_MAC_IOCB_RSP_ERR_OVERSIZE:
		stats->rx_oversize_err++;
		break;
	case IB_MAC_IOCB_RSP_ERR_UNDERSIZE:
		stats->rx_undersize_err++;
		break;
	case IB_MAC_IOCB_RSP_ERR_PREAMBLE:
		stats->rx_preamble_err++;
		break;
	case IB_MAC_IOCB_RSP_ERR_FRAME_LEN:
		stats->rx_frame_len_err++;
		break;
	case IB_MAC_IOCB_RSP_ERR_CRC:
		stats->rx_crc_err++;
	default:
		break;
	}
}