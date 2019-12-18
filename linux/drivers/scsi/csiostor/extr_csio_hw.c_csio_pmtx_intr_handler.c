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
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
#define  DB_OPTIONS_PAR_ERROR_F 135 
#define  ICSPI_PAR_ERROR_F 134 
#define  OESPI_PAR_ERROR_F 133 
#define  PCMD_LEN_OVFL0_F 132 
#define  PCMD_LEN_OVFL1_F 131 
#define  PCMD_LEN_OVFL2_F 130 
#define  PMTX_C_PCMD_PAR_ERROR_F 129 
 int /*<<< orphan*/  PM_TX_INT_CAUSE_A ; 
#define  ZERO_C_CMD_ERROR_F 128 
 scalar_t__ csio_handle_intr_status (struct csio_hw*,int /*<<< orphan*/ ,struct intr_info*) ; 
 int /*<<< orphan*/  csio_hw_fatal_err (struct csio_hw*) ; 

__attribute__((used)) static void csio_pmtx_intr_handler(struct csio_hw *hw)
{
	static struct intr_info pmtx_intr_info[] = {
		{ PCMD_LEN_OVFL0_F, "PMTX channel 0 pcmd too large", -1, 1 },
		{ PCMD_LEN_OVFL1_F, "PMTX channel 1 pcmd too large", -1, 1 },
		{ PCMD_LEN_OVFL2_F, "PMTX channel 2 pcmd too large", -1, 1 },
		{ ZERO_C_CMD_ERROR_F, "PMTX 0-length pcmd", -1, 1 },
		{ 0xffffff0, "PMTX framing error", -1, 1 },
		{ OESPI_PAR_ERROR_F, "PMTX oespi parity error", -1, 1 },
		{ DB_OPTIONS_PAR_ERROR_F, "PMTX db_options parity error", -1,
		  1 },
		{ ICSPI_PAR_ERROR_F, "PMTX icspi parity error", -1, 1 },
		{ PMTX_C_PCMD_PAR_ERROR_F, "PMTX c_pcmd parity error", -1, 1},
		{ 0, NULL, 0, 0 }
	};

	if (csio_handle_intr_status(hw, PM_TX_INT_CAUSE_A, pmtx_intr_info))
		csio_hw_fatal_err(hw);
}