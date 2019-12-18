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
typedef  int PI_UINT32 ;
typedef  int /*<<< orphan*/  DFX_board_t ;

/* Variables and functions */
 int DFX_K_HW_TIMEOUT ; 
 int DFX_K_SUCCESS ; 
 int PI_PCTRL_M_BLAST_FLASH ; 
 int PI_PCTRL_M_CMD_ERROR ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_HOST_DATA ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_CTRL ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_DATA_A ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_DATA_B ; 
 int /*<<< orphan*/  dfx_port_read_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dfx_port_write_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dfx_hw_port_ctrl_req(
	DFX_board_t	*bp,
	PI_UINT32	command,
	PI_UINT32	data_a,
	PI_UINT32	data_b,
	PI_UINT32	*host_data
	)

	{
	PI_UINT32	port_cmd;		/* Port Control command register value */
	int			timeout_cnt;	/* used in for loops */

	/* Set Command Error bit in command longword */

	port_cmd = (PI_UINT32) (command | PI_PCTRL_M_CMD_ERROR);

	/* Issue port command to the adapter */

	dfx_port_write_long(bp, PI_PDQ_K_REG_PORT_DATA_A, data_a);
	dfx_port_write_long(bp, PI_PDQ_K_REG_PORT_DATA_B, data_b);
	dfx_port_write_long(bp, PI_PDQ_K_REG_PORT_CTRL, port_cmd);

	/* Now wait for command to complete */

	if (command == PI_PCTRL_M_BLAST_FLASH)
		timeout_cnt = 600000;	/* set command timeout count to 60 seconds */
	else
		timeout_cnt = 20000;	/* set command timeout count to 2 seconds */

	for (; timeout_cnt > 0; timeout_cnt--)
		{
		dfx_port_read_long(bp, PI_PDQ_K_REG_PORT_CTRL, &port_cmd);
		if (!(port_cmd & PI_PCTRL_M_CMD_ERROR))
			break;
		udelay(100);			/* wait for 100 microseconds */
		}
	if (timeout_cnt == 0)
		return DFX_K_HW_TIMEOUT;

	/*
	 * If the address of host_data is non-zero, assume caller has supplied a
	 * non NULL pointer, and return the contents of the HOST_DATA register in
	 * it.
	 */

	if (host_data != NULL)
		dfx_port_read_long(bp, PI_PDQ_K_REG_HOST_DATA, host_data);
	return DFX_K_SUCCESS;
	}