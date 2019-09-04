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
struct qed_tlv_parsed_buf {int /*<<< orphan*/ * p_val; } ;
struct qed_mfw_tlv_iscsi {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_bytes_set; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_frames_set; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_bytes_set; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_frames_set; int /*<<< orphan*/  rx_desc_qdepth; int /*<<< orphan*/  rx_desc_qdepth_set; int /*<<< orphan*/  tx_desc_qdepth; int /*<<< orphan*/  tx_desc_qdepth_set; int /*<<< orphan*/  boot_progress; int /*<<< orphan*/  boot_progress_set; int /*<<< orphan*/  rx_desc_size; int /*<<< orphan*/  rx_desc_size_set; int /*<<< orphan*/  tx_desc_size; int /*<<< orphan*/  tx_desc_size_set; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  frame_size_set; int /*<<< orphan*/  boot_taget_portal; int /*<<< orphan*/  boot_taget_portal_set; int /*<<< orphan*/  auth_method; int /*<<< orphan*/  auth_method_set; int /*<<< orphan*/  data_digest; int /*<<< orphan*/  data_digest_set; int /*<<< orphan*/  header_digest; int /*<<< orphan*/  header_digest_set; int /*<<< orphan*/  target_llmnr; int /*<<< orphan*/  target_llmnr_set; } ;
struct qed_drv_tlv_hdr {int tlv_type; } ;

/* Variables and functions */
#define  DRV_TLV_AUTHENTICATION_METHOD 142 
#define  DRV_TLV_DATA_DIGEST_FLAG_ENABLED 141 
#define  DRV_TLV_HEADER_DIGEST_FLAG_ENABLED 140 
#define  DRV_TLV_ISCSI_BOOT_PROGRESS 139 
#define  DRV_TLV_ISCSI_BOOT_TARGET_PORTAL 138 
#define  DRV_TLV_ISCSI_PDU_RX_BYTES_RECEIVED 137 
#define  DRV_TLV_ISCSI_PDU_RX_FRAMES_RECEIVED 136 
#define  DRV_TLV_ISCSI_PDU_TX_BYTES_SENT 135 
#define  DRV_TLV_ISCSI_PDU_TX_FRAMES_SENT 134 
#define  DRV_TLV_MAX_FRAME_SIZE 133 
#define  DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_AVG_DEPTH 132 
#define  DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_SIZE 131 
#define  DRV_TLV_PDU_TX_DESCRIPTORS_QUEUE_SIZE 130 
#define  DRV_TLV_PDU_TX_DESCRIPTOR_QUEUE_AVG_DEPTH 129 
#define  DRV_TLV_TARGET_LLMNR_ENABLED 128 

__attribute__((used)) static int
qed_mfw_get_iscsi_tlv_value(struct qed_drv_tlv_hdr *p_tlv,
			    struct qed_mfw_tlv_iscsi *p_drv_buf,
			    struct qed_tlv_parsed_buf *p_buf)
{
	switch (p_tlv->tlv_type) {
	case DRV_TLV_TARGET_LLMNR_ENABLED:
		if (p_drv_buf->target_llmnr_set) {
			p_buf->p_val = &p_drv_buf->target_llmnr;
			return sizeof(p_drv_buf->target_llmnr);
		}
		break;
	case DRV_TLV_HEADER_DIGEST_FLAG_ENABLED:
		if (p_drv_buf->header_digest_set) {
			p_buf->p_val = &p_drv_buf->header_digest;
			return sizeof(p_drv_buf->header_digest);
		}
		break;
	case DRV_TLV_DATA_DIGEST_FLAG_ENABLED:
		if (p_drv_buf->data_digest_set) {
			p_buf->p_val = &p_drv_buf->data_digest;
			return sizeof(p_drv_buf->data_digest);
		}
		break;
	case DRV_TLV_AUTHENTICATION_METHOD:
		if (p_drv_buf->auth_method_set) {
			p_buf->p_val = &p_drv_buf->auth_method;
			return sizeof(p_drv_buf->auth_method);
		}
		break;
	case DRV_TLV_ISCSI_BOOT_TARGET_PORTAL:
		if (p_drv_buf->boot_taget_portal_set) {
			p_buf->p_val = &p_drv_buf->boot_taget_portal;
			return sizeof(p_drv_buf->boot_taget_portal);
		}
		break;
	case DRV_TLV_MAX_FRAME_SIZE:
		if (p_drv_buf->frame_size_set) {
			p_buf->p_val = &p_drv_buf->frame_size;
			return sizeof(p_drv_buf->frame_size);
		}
		break;
	case DRV_TLV_PDU_TX_DESCRIPTORS_QUEUE_SIZE:
		if (p_drv_buf->tx_desc_size_set) {
			p_buf->p_val = &p_drv_buf->tx_desc_size;
			return sizeof(p_drv_buf->tx_desc_size);
		}
		break;
	case DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_SIZE:
		if (p_drv_buf->rx_desc_size_set) {
			p_buf->p_val = &p_drv_buf->rx_desc_size;
			return sizeof(p_drv_buf->rx_desc_size);
		}
		break;
	case DRV_TLV_ISCSI_BOOT_PROGRESS:
		if (p_drv_buf->boot_progress_set) {
			p_buf->p_val = &p_drv_buf->boot_progress;
			return sizeof(p_drv_buf->boot_progress);
		}
		break;
	case DRV_TLV_PDU_TX_DESCRIPTOR_QUEUE_AVG_DEPTH:
		if (p_drv_buf->tx_desc_qdepth_set) {
			p_buf->p_val = &p_drv_buf->tx_desc_qdepth;
			return sizeof(p_drv_buf->tx_desc_qdepth);
		}
		break;
	case DRV_TLV_PDU_RX_DESCRIPTORS_QUEUE_AVG_DEPTH:
		if (p_drv_buf->rx_desc_qdepth_set) {
			p_buf->p_val = &p_drv_buf->rx_desc_qdepth;
			return sizeof(p_drv_buf->rx_desc_qdepth);
		}
		break;
	case DRV_TLV_ISCSI_PDU_RX_FRAMES_RECEIVED:
		if (p_drv_buf->rx_frames_set) {
			p_buf->p_val = &p_drv_buf->rx_frames;
			return sizeof(p_drv_buf->rx_frames);
		}
		break;
	case DRV_TLV_ISCSI_PDU_RX_BYTES_RECEIVED:
		if (p_drv_buf->rx_bytes_set) {
			p_buf->p_val = &p_drv_buf->rx_bytes;
			return sizeof(p_drv_buf->rx_bytes);
		}
		break;
	case DRV_TLV_ISCSI_PDU_TX_FRAMES_SENT:
		if (p_drv_buf->tx_frames_set) {
			p_buf->p_val = &p_drv_buf->tx_frames;
			return sizeof(p_drv_buf->tx_frames);
		}
		break;
	case DRV_TLV_ISCSI_PDU_TX_BYTES_SENT:
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