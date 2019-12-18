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
#define  SIPC_RX_DATA_UNDERFLOW_ERR 138 
 int const SIPC_RX_ERR_BASE ; 
 int SIPC_RX_ERR_MSK ; 
#define  SIPC_RX_FIS_STATUS_BSY_BIT_ERR 137 
#define  SIPC_RX_FIS_STATUS_ERR_BIT_VLD 136 
#define  SIPC_RX_NCQ_WRSETUP_AUTO_ACTIVE_ERR 135 
#define  SIPC_RX_NCQ_WRSETUP_OFFSET_ERR 134 
#define  SIPC_RX_PIO_WRSETUP_STATUS_DRQ_ERR 133 
#define  SIPC_RX_SATA_UNEXP_FIS_ERR 132 
#define  SIPC_RX_WRDATA_LEN_NOT_MATCH_ERR 131 
#define  SIPC_RX_WRSETUP_ESTATUS_ERR 130 
#define  SIPC_RX_WRSETUP_LEN_ODD_ERR 129 
#define  SIPC_RX_WRSETUP_LEN_ZERO_ERR 128 

__attribute__((used)) static int parse_sipc_rx_err_code_v2_hw(u32 err_msk)
{
	static const u8 sipc_rx_err_code_prio[] = {
		SIPC_RX_FIS_STATUS_ERR_BIT_VLD,
		SIPC_RX_PIO_WRSETUP_STATUS_DRQ_ERR,
		SIPC_RX_FIS_STATUS_BSY_BIT_ERR,
		SIPC_RX_WRSETUP_LEN_ODD_ERR,
		SIPC_RX_WRSETUP_LEN_ZERO_ERR,
		SIPC_RX_WRDATA_LEN_NOT_MATCH_ERR,
		SIPC_RX_NCQ_WRSETUP_OFFSET_ERR,
		SIPC_RX_NCQ_WRSETUP_AUTO_ACTIVE_ERR,
		SIPC_RX_SATA_UNEXP_FIS_ERR,
		SIPC_RX_WRSETUP_ESTATUS_ERR,
		SIPC_RX_DATA_UNDERFLOW_ERR,
	};
	int index, i;

	for (i = 0; i < ARRAY_SIZE(sipc_rx_err_code_prio); i++) {
		index = sipc_rx_err_code_prio[i] - SIPC_RX_ERR_BASE;
		err_msk = err_msk & SIPC_RX_ERR_MSK;
		if (err_msk & (1 << (index + 0x10)))
			return sipc_rx_err_code_prio[i];
	}
	return -1;
}