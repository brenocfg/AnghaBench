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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct task_status_struct {void* stat; void* residual; void* open_rej_reason; int /*<<< orphan*/  resp; } ;
struct sas_task {int task_proto; struct task_status_struct task_status; } ;
struct hisi_sas_slot {int abort; } ;
struct hisi_sas_err_record_v2 {int /*<<< orphan*/  dma_rx_err_type; int /*<<< orphan*/  sipc_rx_err_type; int /*<<< orphan*/  dma_tx_err_type; int /*<<< orphan*/  trans_rx_fail_type; int /*<<< orphan*/  trans_tx_fail_type; } ;
struct hisi_hba {int dummy; } ;

/* Variables and functions */
#define  DMA_RX_DATA_LEN_OVERFLOW 214 
#define  DMA_RX_DATA_LEN_UNDERFLOW 213 
#define  DMA_RX_DATA_OFFSET_ERR 212 
#define  DMA_RX_DATA_SGL_OVERFLOW 211 
#define  DMA_RX_PIO_DATA_LEN_ERR 210 
#define  DMA_RX_RDSETUP_ACTIVE_ERR 209 
#define  DMA_RX_RDSETUP_ESTATUS_ERR 208 
#define  DMA_RX_RDSETUP_LEN_ODD_ERR 207 
#define  DMA_RX_RDSETUP_LEN_OVER_ERR 206 
#define  DMA_RX_RDSETUP_LEN_ZERO_ERR 205 
#define  DMA_RX_RDSETUP_OFFSET_ERR 204 
#define  DMA_RX_RDSETUP_STATUS_BSY_ERR 203 
#define  DMA_RX_RDSETUP_STATUS_DRQ_ERR 202 
#define  DMA_RX_RDSETUP_STATUS_ERR 201 
#define  DMA_RX_RESP_BUF_OVERFLOW 200 
#define  DMA_RX_SATA_FRAME_TYPE_ERR 199 
#define  DMA_RX_UNEXP_NORM_RESP_ERR 198 
#define  DMA_RX_UNEXP_RDFRAME_ERR 197 
#define  DMA_RX_UNKNOWN_FRM_ERR 196 
#define  DMA_TX_DATA_SGL_OVERFLOW 195 
#define  DMA_TX_UNEXP_RETRANS_ERR 194 
#define  DMA_TX_UNEXP_XFER_ERR 193 
#define  DMA_TX_XFER_LEN_OVERFLOW 192 
#define  DMA_TX_XFER_OFFSET_ERR 191 
 void* SAM_STAT_CHECK_CONDITION ; 
 void* SAS_DATA_OVERRUN ; 
 void* SAS_DATA_UNDERRUN ; 
 void* SAS_DEV_NO_RESPONSE ; 
 void* SAS_OPEN_REJECT ; 
 void* SAS_OREJ_BAD_DEST ; 
 void* SAS_OREJ_CONN_RATE ; 
 void* SAS_OREJ_EPROTO ; 
 void* SAS_OREJ_NO_DEST ; 
 void* SAS_OREJ_UNKNOWN ; 
 void* SAS_OREJ_WRONG_DEST ; 
 void* SAS_PHY_DOWN ; 
#define  SAS_PROTOCOL_SATA 190 
#define  SAS_PROTOCOL_SMP 189 
#define  SAS_PROTOCOL_SSP 188 
#define  SAS_PROTOCOL_STP 187 
 void* SAS_PROTO_RESPONSE ; 
 void* SAS_QUEUE_FULL ; 
 int /*<<< orphan*/  SAS_TASK_UNDELIVERED ; 
#define  SIPC_RX_DATA_UNDERFLOW_ERR 186 
#define  SIPC_RX_FIS_STATUS_BSY_BIT_ERR 185 
#define  SIPC_RX_FIS_STATUS_ERR_BIT_VLD 184 
#define  SIPC_RX_PIO_WRSETUP_STATUS_DRQ_ERR 183 
#define  SIPC_RX_SATA_UNEXP_FIS_ERR 182 
#define  SIPC_RX_WRDATA_LEN_NOT_MATCH_ERR 181 
#define  SIPC_RX_WRSETUP_LEN_ODD_ERR 180 
#define  SIPC_RX_WRSETUP_LEN_ZERO_ERR 179 
#define  TRANS_RX_ERR_WITH_BAD_FRM_TYPE 178 
#define  TRANS_RX_ERR_WITH_BAD_HASH 177 
#define  TRANS_RX_ERR_WITH_BREAK_RECEVIED 176 
#define  TRANS_RX_ERR_WITH_BREAK_REQUEST 175 
#define  TRANS_RX_ERR_WITH_BREAK_TIMEOUT 174 
#define  TRANS_RX_ERR_WITH_CLOSE_COMINIT 173 
#define  TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT 172 
#define  TRANS_RX_ERR_WITH_CLOSE_NORMAL 171 
#define  TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE 170 
#define  TRANS_RX_ERR_WITH_DATA_LEN0 169 
#define  TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN 168 
#define  TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR 167 
#define  TRANS_RX_ERR_WITH_RXFIS_CRC_ERR 166 
#define  TRANS_RX_ERR_WITH_RXFIS_DECODE_ERROR 165 
#define  TRANS_RX_ERR_WITH_RXFIS_RX_SYNCP 164 
#define  TRANS_RX_ERR_WITH_RXFRAME_CRC_ERR 163 
#define  TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM 162 
#define  TRANS_RX_ERR_WITH_RXFRAME_LENGTH_OVERRUN 161 
#define  TRANS_RX_SSP_FRM_LEN_ERR 160 
#define  TRANS_RX_XRDY_WLEN_ZERO_ERR 159 
#define  TRANS_TX_ERR_FRAME_TXED 158 
#define  TRANS_TX_ERR_PHY_NOT_ENABLE 157 
#define  TRANS_TX_ERR_WITH_ACK_NAK_TIMEOUT 156 
#define  TRANS_TX_ERR_WITH_BREAK_RECEVIED 155 
#define  TRANS_TX_ERR_WITH_BREAK_REQUEST 154 
#define  TRANS_TX_ERR_WITH_BREAK_TIMEOUT 153 
#define  TRANS_TX_ERR_WITH_CLOSE_COMINIT 152 
#define  TRANS_TX_ERR_WITH_CLOSE_DWS_TIMEOUT 151 
#define  TRANS_TX_ERR_WITH_CLOSE_NORMAL 150 
#define  TRANS_TX_ERR_WITH_CLOSE_PHYDISALE 149 
#define  TRANS_TX_ERR_WITH_CLOSE_TIMEOUT 148 
#define  TRANS_TX_ERR_WITH_CREDIT_TIMEOUT 147 
#define  TRANS_TX_ERR_WITH_IPTT_CONFLICT 146 
#define  TRANS_TX_ERR_WITH_NAK_RECEVIED 145 
#define  TRANS_TX_ERR_WITH_OPEN_BY_DES_OR_OTHERS 144 
#define  TRANS_TX_ERR_WITH_WAIT_RECV_TIMEOUT 143 
#define  TRANS_TX_OPEN_CNX_ERR_AIP_TIMEOUT 142 
#define  TRANS_TX_OPEN_CNX_ERR_BAD_DESTINATION 141 
#define  TRANS_TX_OPEN_CNX_ERR_BREAK_RCVD 140 
#define  TRANS_TX_OPEN_CNX_ERR_BY_OTHER 139 
#define  TRANS_TX_OPEN_CNX_ERR_CONNECTION_RATE_NOT_SUPPORTED 138 
#define  TRANS_TX_OPEN_CNX_ERR_LOW_PHY_POWER 137 
#define  TRANS_TX_OPEN_CNX_ERR_NO_DESTINATION 136 
#define  TRANS_TX_OPEN_CNX_ERR_OPEN_TIMEOUT 135 
#define  TRANS_TX_OPEN_CNX_ERR_PATHWAY_BLOCKED 134 
#define  TRANS_TX_OPEN_CNX_ERR_PROTOCOL_NOT_SUPPORTED 133 
#define  TRANS_TX_OPEN_CNX_ERR_STP_RESOURCES_BUSY 132 
#define  TRANS_TX_OPEN_CNX_ERR_WRONG_DESTINATION 131 
#define  TRANS_TX_OPEN_CNX_ERR_ZONE_VIOLATION 130 
#define  TRANS_TX_OPEN_FAIL_WITH_IT_NEXUS_LOSS 129 
#define  TRANS_TX_OPEN_RETRY_ERR_THRESHOLD_REACHED 128 
 int /*<<< orphan*/  hisi_sas_sata_done (struct sas_task*,struct hisi_sas_slot*) ; 
 struct hisi_sas_err_record_v2* hisi_sas_status_buf_addr_mem (struct hisi_sas_slot*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int parse_dma_rx_err_code_v2_hw (void*) ; 
 int parse_dma_tx_err_code_v2_hw (int /*<<< orphan*/ ) ; 
 int parse_sipc_rx_err_code_v2_hw (int /*<<< orphan*/ ) ; 
 int parse_trans_rx_err_code_v2_hw (void*) ; 
 int parse_trans_tx_err_code_v2_hw (void*) ; 

__attribute__((used)) static void slot_err_v2_hw(struct hisi_hba *hisi_hba,
			   struct sas_task *task,
			   struct hisi_sas_slot *slot,
			   int err_phase)
{
	struct task_status_struct *ts = &task->task_status;
	struct hisi_sas_err_record_v2 *err_record =
			hisi_sas_status_buf_addr_mem(slot);
	u32 trans_tx_fail_type = le32_to_cpu(err_record->trans_tx_fail_type);
	u32 trans_rx_fail_type = le32_to_cpu(err_record->trans_rx_fail_type);
	u16 dma_tx_err_type = le16_to_cpu(err_record->dma_tx_err_type);
	u16 sipc_rx_err_type = le16_to_cpu(err_record->sipc_rx_err_type);
	u32 dma_rx_err_type = le32_to_cpu(err_record->dma_rx_err_type);
	int error = -1;

	if (err_phase == 1) {
		/* error in TX phase, the priority of error is: DW2 > DW0 */
		error = parse_dma_tx_err_code_v2_hw(dma_tx_err_type);
		if (error == -1)
			error = parse_trans_tx_err_code_v2_hw(
					trans_tx_fail_type);
	} else if (err_phase == 2) {
		/* error in RX phase, the priority is: DW1 > DW3 > DW2 */
		error = parse_trans_rx_err_code_v2_hw(trans_rx_fail_type);
		if (error == -1) {
			error = parse_dma_rx_err_code_v2_hw(
					dma_rx_err_type);
			if (error == -1)
				error = parse_sipc_rx_err_code_v2_hw(
						sipc_rx_err_type);
		}
	}

	switch (task->task_proto) {
	case SAS_PROTOCOL_SSP:
	{
		switch (error) {
		case TRANS_TX_OPEN_CNX_ERR_NO_DESTINATION:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_NO_DEST;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_PROTOCOL_NOT_SUPPORTED:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_EPROTO;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_CONNECTION_RATE_NOT_SUPPORTED:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_CONN_RATE;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_BAD_DESTINATION:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_BAD_DEST;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_WRONG_DESTINATION:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_WRONG_DEST;
			break;
		}
		case DMA_RX_UNEXP_NORM_RESP_ERR:
		case TRANS_TX_OPEN_CNX_ERR_ZONE_VIOLATION:
		case DMA_RX_RESP_BUF_OVERFLOW:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_UNKNOWN;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_LOW_PHY_POWER:
		{
			/* not sure */
			ts->stat = SAS_DEV_NO_RESPONSE;
			break;
		}
		case DMA_RX_DATA_LEN_OVERFLOW:
		{
			ts->stat = SAS_DATA_OVERRUN;
			ts->residual = 0;
			break;
		}
		case DMA_RX_DATA_LEN_UNDERFLOW:
		{
			ts->residual = trans_tx_fail_type;
			ts->stat = SAS_DATA_UNDERRUN;
			break;
		}
		case TRANS_TX_OPEN_FAIL_WITH_IT_NEXUS_LOSS:
		case TRANS_TX_ERR_PHY_NOT_ENABLE:
		case TRANS_TX_OPEN_CNX_ERR_BY_OTHER:
		case TRANS_TX_OPEN_CNX_ERR_AIP_TIMEOUT:
		case TRANS_TX_OPEN_CNX_ERR_BREAK_RCVD:
		case TRANS_TX_OPEN_CNX_ERR_PATHWAY_BLOCKED:
		case TRANS_TX_OPEN_CNX_ERR_OPEN_TIMEOUT:
		case TRANS_TX_OPEN_RETRY_ERR_THRESHOLD_REACHED:
		case TRANS_TX_ERR_WITH_BREAK_TIMEOUT:
		case TRANS_TX_ERR_WITH_BREAK_REQUEST:
		case TRANS_TX_ERR_WITH_BREAK_RECEVIED:
		case TRANS_TX_ERR_WITH_CLOSE_TIMEOUT:
		case TRANS_TX_ERR_WITH_CLOSE_NORMAL:
		case TRANS_TX_ERR_WITH_CLOSE_PHYDISALE:
		case TRANS_TX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		case TRANS_TX_ERR_WITH_CLOSE_COMINIT:
		case TRANS_TX_ERR_WITH_NAK_RECEVIED:
		case TRANS_TX_ERR_WITH_ACK_NAK_TIMEOUT:
		case TRANS_TX_ERR_WITH_CREDIT_TIMEOUT:
		case TRANS_TX_ERR_WITH_IPTT_CONFLICT:
		case TRANS_RX_ERR_WITH_RXFRAME_CRC_ERR:
		case TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR:
		case TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM:
		case TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN:
		case TRANS_RX_ERR_WITH_BREAK_TIMEOUT:
		case TRANS_RX_ERR_WITH_BREAK_REQUEST:
		case TRANS_RX_ERR_WITH_BREAK_RECEVIED:
		case TRANS_RX_ERR_WITH_CLOSE_NORMAL:
		case TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		case TRANS_RX_ERR_WITH_CLOSE_COMINIT:
		case TRANS_TX_ERR_FRAME_TXED:
		case TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE:
		case TRANS_RX_ERR_WITH_DATA_LEN0:
		case TRANS_RX_ERR_WITH_BAD_HASH:
		case TRANS_RX_XRDY_WLEN_ZERO_ERR:
		case TRANS_RX_SSP_FRM_LEN_ERR:
		case TRANS_RX_ERR_WITH_BAD_FRM_TYPE:
		case DMA_TX_DATA_SGL_OVERFLOW:
		case DMA_TX_UNEXP_XFER_ERR:
		case DMA_TX_UNEXP_RETRANS_ERR:
		case DMA_TX_XFER_LEN_OVERFLOW:
		case DMA_TX_XFER_OFFSET_ERR:
		case SIPC_RX_DATA_UNDERFLOW_ERR:
		case DMA_RX_DATA_SGL_OVERFLOW:
		case DMA_RX_DATA_OFFSET_ERR:
		case DMA_RX_RDSETUP_LEN_ODD_ERR:
		case DMA_RX_RDSETUP_LEN_ZERO_ERR:
		case DMA_RX_RDSETUP_LEN_OVER_ERR:
		case DMA_RX_SATA_FRAME_TYPE_ERR:
		case DMA_RX_UNKNOWN_FRM_ERR:
		{
			/* This will request a retry */
			ts->stat = SAS_QUEUE_FULL;
			slot->abort = 1;
			break;
		}
		default:
			break;
		}
	}
		break;
	case SAS_PROTOCOL_SMP:
		ts->stat = SAM_STAT_CHECK_CONDITION;
		break;

	case SAS_PROTOCOL_SATA:
	case SAS_PROTOCOL_STP:
	case SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
	{
		switch (error) {
		case TRANS_TX_OPEN_CNX_ERR_NO_DESTINATION:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_NO_DEST;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_LOW_PHY_POWER:
		{
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_DEV_NO_RESPONSE;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_PROTOCOL_NOT_SUPPORTED:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_EPROTO;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_CONNECTION_RATE_NOT_SUPPORTED:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_CONN_RATE;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_BAD_DESTINATION:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_CONN_RATE;
			break;
		}
		case TRANS_TX_OPEN_CNX_ERR_WRONG_DESTINATION:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_WRONG_DEST;
			break;
		}
		case DMA_RX_RESP_BUF_OVERFLOW:
		case DMA_RX_UNEXP_NORM_RESP_ERR:
		case TRANS_TX_OPEN_CNX_ERR_ZONE_VIOLATION:
		{
			ts->stat = SAS_OPEN_REJECT;
			ts->open_rej_reason = SAS_OREJ_UNKNOWN;
			break;
		}
		case DMA_RX_DATA_LEN_OVERFLOW:
		{
			ts->stat = SAS_DATA_OVERRUN;
			ts->residual = 0;
			break;
		}
		case DMA_RX_DATA_LEN_UNDERFLOW:
		{
			ts->residual = trans_tx_fail_type;
			ts->stat = SAS_DATA_UNDERRUN;
			break;
		}
		case TRANS_TX_OPEN_FAIL_WITH_IT_NEXUS_LOSS:
		case TRANS_TX_ERR_PHY_NOT_ENABLE:
		case TRANS_TX_OPEN_CNX_ERR_BY_OTHER:
		case TRANS_TX_OPEN_CNX_ERR_AIP_TIMEOUT:
		case TRANS_TX_OPEN_CNX_ERR_BREAK_RCVD:
		case TRANS_TX_OPEN_CNX_ERR_PATHWAY_BLOCKED:
		case TRANS_TX_OPEN_CNX_ERR_OPEN_TIMEOUT:
		case TRANS_TX_OPEN_RETRY_ERR_THRESHOLD_REACHED:
		case TRANS_TX_ERR_WITH_BREAK_TIMEOUT:
		case TRANS_TX_ERR_WITH_BREAK_REQUEST:
		case TRANS_TX_ERR_WITH_BREAK_RECEVIED:
		case TRANS_TX_ERR_WITH_CLOSE_TIMEOUT:
		case TRANS_TX_ERR_WITH_CLOSE_NORMAL:
		case TRANS_TX_ERR_WITH_CLOSE_PHYDISALE:
		case TRANS_TX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		case TRANS_TX_ERR_WITH_CLOSE_COMINIT:
		case TRANS_TX_ERR_WITH_ACK_NAK_TIMEOUT:
		case TRANS_TX_ERR_WITH_CREDIT_TIMEOUT:
		case TRANS_TX_ERR_WITH_OPEN_BY_DES_OR_OTHERS:
		case TRANS_TX_ERR_WITH_WAIT_RECV_TIMEOUT:
		case TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM:
		case TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR:
		case TRANS_RX_ERR_WITH_RXFIS_DECODE_ERROR:
		case TRANS_RX_ERR_WITH_RXFIS_CRC_ERR:
		case TRANS_RX_ERR_WITH_RXFRAME_LENGTH_OVERRUN:
		case TRANS_RX_ERR_WITH_RXFIS_RX_SYNCP:
		case TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN:
		case TRANS_RX_ERR_WITH_BREAK_TIMEOUT:
		case TRANS_RX_ERR_WITH_BREAK_REQUEST:
		case TRANS_RX_ERR_WITH_BREAK_RECEVIED:
		case TRANS_RX_ERR_WITH_CLOSE_NORMAL:
		case TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE:
		case TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		case TRANS_RX_ERR_WITH_CLOSE_COMINIT:
		case TRANS_RX_ERR_WITH_DATA_LEN0:
		case TRANS_RX_ERR_WITH_BAD_HASH:
		case TRANS_RX_XRDY_WLEN_ZERO_ERR:
		case TRANS_RX_ERR_WITH_BAD_FRM_TYPE:
		case DMA_TX_DATA_SGL_OVERFLOW:
		case DMA_TX_UNEXP_XFER_ERR:
		case DMA_TX_UNEXP_RETRANS_ERR:
		case DMA_TX_XFER_LEN_OVERFLOW:
		case DMA_TX_XFER_OFFSET_ERR:
		case SIPC_RX_FIS_STATUS_ERR_BIT_VLD:
		case SIPC_RX_PIO_WRSETUP_STATUS_DRQ_ERR:
		case SIPC_RX_FIS_STATUS_BSY_BIT_ERR:
		case SIPC_RX_WRSETUP_LEN_ODD_ERR:
		case SIPC_RX_WRSETUP_LEN_ZERO_ERR:
		case SIPC_RX_WRDATA_LEN_NOT_MATCH_ERR:
		case SIPC_RX_SATA_UNEXP_FIS_ERR:
		case DMA_RX_DATA_SGL_OVERFLOW:
		case DMA_RX_DATA_OFFSET_ERR:
		case DMA_RX_SATA_FRAME_TYPE_ERR:
		case DMA_RX_UNEXP_RDFRAME_ERR:
		case DMA_RX_PIO_DATA_LEN_ERR:
		case DMA_RX_RDSETUP_STATUS_ERR:
		case DMA_RX_RDSETUP_STATUS_DRQ_ERR:
		case DMA_RX_RDSETUP_STATUS_BSY_ERR:
		case DMA_RX_RDSETUP_LEN_ODD_ERR:
		case DMA_RX_RDSETUP_LEN_ZERO_ERR:
		case DMA_RX_RDSETUP_LEN_OVER_ERR:
		case DMA_RX_RDSETUP_OFFSET_ERR:
		case DMA_RX_RDSETUP_ACTIVE_ERR:
		case DMA_RX_RDSETUP_ESTATUS_ERR:
		case DMA_RX_UNKNOWN_FRM_ERR:
		case TRANS_RX_SSP_FRM_LEN_ERR:
		case TRANS_TX_OPEN_CNX_ERR_STP_RESOURCES_BUSY:
		{
			slot->abort = 1;
			ts->stat = SAS_PHY_DOWN;
			break;
		}
		default:
		{
			ts->stat = SAS_PROTO_RESPONSE;
			break;
		}
		}
		hisi_sas_sata_done(task, slot);
	}
		break;
	default:
		break;
	}
}