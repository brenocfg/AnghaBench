#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* link_available; TYPE_1__* dev; scalar_t__ reset_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  int PI_UINT32 ;
typedef  TYPE_2__ DFX_board_t ;

/* Variables and functions */
 scalar_t__ DFX_K_SUCCESS ; 
 int PI_HOST_INT_K_DISABLE_ALL_INTS ; 
 void* PI_K_FALSE ; 
 void* PI_K_TRUE ; 
 int /*<<< orphan*/  PI_PCTRL_M_XMT_DATA_FLUSH_DONE ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_HOST_INT_ENB ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_TYPE_0_STATUS ; 
 int PI_STATE_K_HALTED ; 
 int PI_STATE_K_LINK_AVAIL ; 
 int PI_TYPE_0_STAT_M_BUS_PAR_ERR ; 
 int PI_TYPE_0_STAT_M_NXM ; 
 int PI_TYPE_0_STAT_M_PM_PAR_ERR ; 
 int PI_TYPE_0_STAT_M_STATE_CHANGE ; 
 int PI_TYPE_0_STAT_M_XMT_FLUSH ; 
 scalar_t__ dfx_adap_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dfx_hw_adap_state_rd (TYPE_2__*) ; 
 int /*<<< orphan*/  dfx_hw_port_ctrl_req (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfx_int_pr_halt_id (TYPE_2__*) ; 
 int /*<<< orphan*/  dfx_port_read_long (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dfx_xmt_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfx_int_type_0_process(DFX_board_t	*bp)

	{
	PI_UINT32	type_0_status;		/* Host Interrupt Type 0 register */
	PI_UINT32	state;				/* current adap state (from port status) */

	/*
	 * Read host interrupt Type 0 register to determine which Type 0
	 * interrupts are pending.  Immediately write it back out to clear
	 * those interrupts.
	 */

	dfx_port_read_long(bp, PI_PDQ_K_REG_TYPE_0_STATUS, &type_0_status);
	dfx_port_write_long(bp, PI_PDQ_K_REG_TYPE_0_STATUS, type_0_status);

	/* Check for Type 0 error interrupts */

	if (type_0_status & (PI_TYPE_0_STAT_M_NXM |
							PI_TYPE_0_STAT_M_PM_PAR_ERR |
							PI_TYPE_0_STAT_M_BUS_PAR_ERR))
		{
		/* Check for Non-Existent Memory error */

		if (type_0_status & PI_TYPE_0_STAT_M_NXM)
			printk("%s: Non-Existent Memory Access Error\n", bp->dev->name);

		/* Check for Packet Memory Parity error */

		if (type_0_status & PI_TYPE_0_STAT_M_PM_PAR_ERR)
			printk("%s: Packet Memory Parity Error\n", bp->dev->name);

		/* Check for Host Bus Parity error */

		if (type_0_status & PI_TYPE_0_STAT_M_BUS_PAR_ERR)
			printk("%s: Host Bus Parity Error\n", bp->dev->name);

		/* Reset adapter and bring it back on-line */

		bp->link_available = PI_K_FALSE;	/* link is no longer available */
		bp->reset_type = 0;					/* rerun on-board diagnostics */
		printk("%s: Resetting adapter...\n", bp->dev->name);
		if (dfx_adap_init(bp, 0) != DFX_K_SUCCESS)
			{
			printk("%s: Adapter reset failed!  Disabling adapter interrupts.\n", bp->dev->name);
			dfx_port_write_long(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);
			return;
			}
		printk("%s: Adapter reset successful!\n", bp->dev->name);
		return;
		}

	/* Check for transmit flush interrupt */

	if (type_0_status & PI_TYPE_0_STAT_M_XMT_FLUSH)
		{
		/* Flush any pending xmt's and acknowledge the flush interrupt */

		bp->link_available = PI_K_FALSE;		/* link is no longer available */
		dfx_xmt_flush(bp);						/* flush any outstanding packets */
		(void) dfx_hw_port_ctrl_req(bp,
									PI_PCTRL_M_XMT_DATA_FLUSH_DONE,
									0,
									0,
									NULL);
		}

	/* Check for adapter state change */

	if (type_0_status & PI_TYPE_0_STAT_M_STATE_CHANGE)
		{
		/* Get latest adapter state */

		state = dfx_hw_adap_state_rd(bp);	/* get adapter state */
		if (state == PI_STATE_K_HALTED)
			{
			/*
			 * Adapter has transitioned to HALTED state, try to reset
			 * adapter to bring it back on-line.  If reset fails,
			 * leave the adapter in the broken state.
			 */

			printk("%s: Controller has transitioned to HALTED state!\n", bp->dev->name);
			dfx_int_pr_halt_id(bp);			/* display halt id as string */

			/* Reset adapter and bring it back on-line */

			bp->link_available = PI_K_FALSE;	/* link is no longer available */
			bp->reset_type = 0;					/* rerun on-board diagnostics */
			printk("%s: Resetting adapter...\n", bp->dev->name);
			if (dfx_adap_init(bp, 0) != DFX_K_SUCCESS)
				{
				printk("%s: Adapter reset failed!  Disabling adapter interrupts.\n", bp->dev->name);
				dfx_port_write_long(bp, PI_PDQ_K_REG_HOST_INT_ENB, PI_HOST_INT_K_DISABLE_ALL_INTS);
				return;
				}
			printk("%s: Adapter reset successful!\n", bp->dev->name);
			}
		else if (state == PI_STATE_K_LINK_AVAIL)
			{
			bp->link_available = PI_K_TRUE;		/* set link available flag */
			}
		}
	}