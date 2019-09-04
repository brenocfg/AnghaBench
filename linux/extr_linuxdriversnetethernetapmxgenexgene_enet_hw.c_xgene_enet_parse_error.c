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
struct xgene_enet_desc_ring {int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_crc_errors; } ;
typedef  enum xgene_enet_err_code { ____Placeholder_xgene_enet_err_code } xgene_enet_err_code ;

/* Variables and functions */
#define  INGRESS_CHECKSUM 134 
#define  INGRESS_CHECKSUM_COMPUTE 133 
#define  INGRESS_CRC 132 
#define  INGRESS_FIFO_OVERRUN 131 
#define  INGRESS_PKT_LEN 130 
#define  INGRESS_PKT_UNDER 129 
#define  INGRESS_TRUNC_FRAME 128 

void xgene_enet_parse_error(struct xgene_enet_desc_ring *ring,
			    enum xgene_enet_err_code status)
{
	switch (status) {
	case INGRESS_CRC:
		ring->rx_crc_errors++;
		break;
	case INGRESS_CHECKSUM:
	case INGRESS_CHECKSUM_COMPUTE:
		ring->rx_errors++;
		break;
	case INGRESS_TRUNC_FRAME:
		ring->rx_frame_errors++;
		break;
	case INGRESS_PKT_LEN:
		ring->rx_length_errors++;
		break;
	case INGRESS_PKT_UNDER:
		ring->rx_frame_errors++;
		break;
	case INGRESS_FIFO_OVERRUN:
		ring->rx_fifo_errors++;
		break;
	default:
		break;
	}
}