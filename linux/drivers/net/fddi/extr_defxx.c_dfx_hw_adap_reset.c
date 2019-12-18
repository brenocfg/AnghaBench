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
typedef  int /*<<< orphan*/  PI_UINT32 ;
typedef  int /*<<< orphan*/  DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_DATA_A ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_PORT_RESET ; 
 int /*<<< orphan*/  PI_RESET_M_ASSERT_RESET ; 
 int /*<<< orphan*/  dfx_port_write_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dfx_hw_adap_reset(
	DFX_board_t	*bp,
	PI_UINT32	type
	)

	{
	/* Set Reset type and assert reset */

	dfx_port_write_long(bp, PI_PDQ_K_REG_PORT_DATA_A, type);	/* tell adapter type of reset */
	dfx_port_write_long(bp, PI_PDQ_K_REG_PORT_RESET, PI_RESET_M_ASSERT_RESET);

	/* Wait for at least 1 Microsecond according to the spec. We wait 20 just to be safe */

	udelay(20);

	/* Deassert reset */

	dfx_port_write_long(bp, PI_PDQ_K_REG_PORT_RESET, 0);
	}