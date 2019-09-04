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
struct qed_tlv_parsed_buf {int* data; int* p_val; } ;
struct TYPE_2__ {int /*<<< orphan*/  lso_supported; int /*<<< orphan*/  ipv4_csum_offload; int /*<<< orphan*/  b_set; } ;
struct qed_mfw_tlv_generic {int** mac; int rx_frames; int rx_bytes; int tx_frames; int tx_bytes; int /*<<< orphan*/  tx_bytes_set; int /*<<< orphan*/  tx_frames_set; int /*<<< orphan*/  rx_bytes_set; int /*<<< orphan*/  rx_frames_set; int /*<<< orphan*/ * mac_set; TYPE_1__ flags; } ;
struct qed_drv_tlv_hdr {int tlv_type; } ;

/* Variables and functions */
#define  DRV_TLV_ADDITIONAL_MAC_ADDR_1 135 
#define  DRV_TLV_ADDITIONAL_MAC_ADDR_2 134 
#define  DRV_TLV_FEATURE_FLAGS 133 
#define  DRV_TLV_LOCAL_ADMIN_ADDR 132 
#define  DRV_TLV_RX_BYTES_RECEIVED 131 
#define  DRV_TLV_RX_FRAMES_RECEIVED 130 
#define  DRV_TLV_TX_BYTES_SENT 129 
#define  DRV_TLV_TX_FRAMES_SENT 128 
 int ETH_ALEN ; 
 int QED_MFW_TLV_FLAGS_SIZE ; 
 int QED_TLV_DATA_MAX ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qed_mfw_get_gen_tlv_value(struct qed_drv_tlv_hdr *p_tlv,
			  struct qed_mfw_tlv_generic *p_drv_buf,
			  struct qed_tlv_parsed_buf *p_buf)
{
	switch (p_tlv->tlv_type) {
	case DRV_TLV_FEATURE_FLAGS:
		if (p_drv_buf->flags.b_set) {
			memset(p_buf->data, 0, sizeof(u8) * QED_TLV_DATA_MAX);
			p_buf->data[0] = p_drv_buf->flags.ipv4_csum_offload ?
			    1 : 0;
			p_buf->data[0] |= (p_drv_buf->flags.lso_supported ?
					   1 : 0) << 1;
			p_buf->p_val = p_buf->data;
			return QED_MFW_TLV_FLAGS_SIZE;
		}
		break;

	case DRV_TLV_LOCAL_ADMIN_ADDR:
	case DRV_TLV_ADDITIONAL_MAC_ADDR_1:
	case DRV_TLV_ADDITIONAL_MAC_ADDR_2:
		{
			int idx = p_tlv->tlv_type - DRV_TLV_LOCAL_ADMIN_ADDR;

			if (p_drv_buf->mac_set[idx]) {
				p_buf->p_val = p_drv_buf->mac[idx];
				return ETH_ALEN;
			}
			break;
		}

	case DRV_TLV_RX_FRAMES_RECEIVED:
		if (p_drv_buf->rx_frames_set) {
			p_buf->p_val = &p_drv_buf->rx_frames;
			return sizeof(p_drv_buf->rx_frames);
		}
		break;
	case DRV_TLV_RX_BYTES_RECEIVED:
		if (p_drv_buf->rx_bytes_set) {
			p_buf->p_val = &p_drv_buf->rx_bytes;
			return sizeof(p_drv_buf->rx_bytes);
		}
		break;
	case DRV_TLV_TX_FRAMES_SENT:
		if (p_drv_buf->tx_frames_set) {
			p_buf->p_val = &p_drv_buf->tx_frames;
			return sizeof(p_drv_buf->tx_frames);
		}
		break;
	case DRV_TLV_TX_BYTES_SENT:
		if (p_drv_buf->tx_bytes_set) {
			p_buf->p_val = &p_drv_buf->tx_bytes;
			return sizeof(p_drv_buf->tx_bytes);
		}
		break;
	default:
		break;
	}

	return -1;
}