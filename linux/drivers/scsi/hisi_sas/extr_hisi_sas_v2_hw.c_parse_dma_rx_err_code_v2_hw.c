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
typedef  int u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
#define  DMA_RX_DATA_LEN_OVERFLOW 153 
#define  DMA_RX_DATA_LEN_UNDERFLOW 152 
#define  DMA_RX_DATA_OFFSET_ERR 151 
#define  DMA_RX_DATA_SGL_OVERFLOW 150 
#define  DMA_RX_DIF_APP_ERR 149 
#define  DMA_RX_DIF_CRC_ERR 148 
#define  DMA_RX_DIF_RPP_ERR 147 
#define  DMA_RX_DIF_SGL_OVERFLOW 146 
 int const DMA_RX_ERR_BASE ; 
#define  DMA_RX_PIO_DATA_LEN_ERR 145 
#define  DMA_RX_RAM_ECC_ERR 144 
#define  DMA_RX_RDSETUP_ACTIVE_ERR 143 
#define  DMA_RX_RDSETUP_ESTATUS_ERR 142 
#define  DMA_RX_RDSETUP_LEN_ODD_ERR 141 
#define  DMA_RX_RDSETUP_LEN_OVER_ERR 140 
#define  DMA_RX_RDSETUP_LEN_ZERO_ERR 139 
#define  DMA_RX_RDSETUP_OFFSET_ERR 138 
#define  DMA_RX_RDSETUP_STATUS_BSY_ERR 137 
#define  DMA_RX_RDSETUP_STATUS_DRQ_ERR 136 
#define  DMA_RX_RDSETUP_STATUS_ERR 135 
#define  DMA_RX_RESP_BUF_OVERFLOW 134 
#define  DMA_RX_SATA_FRAME_TYPE_ERR 133 
#define  DMA_RX_UNEXP_NORM_RESP_ERR 132 
#define  DMA_RX_UNEXP_RDFRAME_ERR 131 
#define  DMA_RX_UNEXP_RETRANS_RESP_ERR 130 
#define  DMA_RX_UNKNOWN_FRM_ERR 129 
#define  RESERVED10 128 

__attribute__((used)) static int parse_dma_rx_err_code_v2_hw(u32 err_msk)
{
	static const u8 dma_rx_err_code_prio[] = {
		DMA_RX_UNKNOWN_FRM_ERR,
		DMA_RX_DATA_LEN_OVERFLOW,
		DMA_RX_DATA_LEN_UNDERFLOW,
		DMA_RX_DATA_OFFSET_ERR,
		RESERVED10,
		DMA_RX_SATA_FRAME_TYPE_ERR,
		DMA_RX_RESP_BUF_OVERFLOW,
		DMA_RX_UNEXP_RETRANS_RESP_ERR,
		DMA_RX_UNEXP_NORM_RESP_ERR,
		DMA_RX_UNEXP_RDFRAME_ERR,
		DMA_RX_PIO_DATA_LEN_ERR,
		DMA_RX_RDSETUP_STATUS_ERR,
		DMA_RX_RDSETUP_STATUS_DRQ_ERR,
		DMA_RX_RDSETUP_STATUS_BSY_ERR,
		DMA_RX_RDSETUP_LEN_ODD_ERR,
		DMA_RX_RDSETUP_LEN_ZERO_ERR,
		DMA_RX_RDSETUP_LEN_OVER_ERR,
		DMA_RX_RDSETUP_OFFSET_ERR,
		DMA_RX_RDSETUP_ACTIVE_ERR,
		DMA_RX_RDSETUP_ESTATUS_ERR,
		DMA_RX_RAM_ECC_ERR,
		DMA_RX_DIF_CRC_ERR,
		DMA_RX_DIF_APP_ERR,
		DMA_RX_DIF_RPP_ERR,
		DMA_RX_DATA_SGL_OVERFLOW,
		DMA_RX_DIF_SGL_OVERFLOW,
	};
	int index, i;

	for (i = 0; i < ARRAY_SIZE(dma_rx_err_code_prio); i++) {
		index = dma_rx_err_code_prio[i] - DMA_RX_ERR_BASE;
		if (err_msk & (1 << index))
			return dma_rx_err_code_prio[i];
	}
	return -1;
}