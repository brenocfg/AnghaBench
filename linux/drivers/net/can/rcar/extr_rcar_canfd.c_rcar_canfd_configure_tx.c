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
typedef  int u32 ;
typedef  int u16 ;
struct rcar_canfd_global {int /*<<< orphan*/  base; scalar_t__ fdmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCANFD_CFCC (int,int /*<<< orphan*/ ) ; 
 int RCANFD_CFCC_CFDC (int) ; 
 int RCANFD_CFCC_CFIM ; 
 int RCANFD_CFCC_CFM (int) ; 
 int RCANFD_CFCC_CFPLS (int) ; 
 int RCANFD_CFCC_CFTML (int) ; 
 int RCANFD_CFCC_CFTXIE ; 
 int /*<<< orphan*/  RCANFD_CFFIFO_IDX ; 
 int /*<<< orphan*/  RCANFD_F_CFFDCSTS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_canfd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_canfd_configure_tx(struct rcar_canfd_global *gpriv, u32 ch)
{
	/* Tx/Rx(Common) FIFO configured in Tx mode is
	 * used for transmission
	 *
	 * Each channel has 3 Common FIFO dedicated to them.
	 * Use the 1st (index 0) out of 3
	 */
	u32 cfg;
	u16 cftml, cfm, cfdc, cfpls;

	cftml = 0;		/* 0th buffer */
	cfm = 1;		/* b01 - Transmit mode */
	cfdc = 2;		/* b010 - 8 messages Tx FIFO depth */
	if (gpriv->fdmode)
		cfpls = 7;	/* b111 - Max 64 bytes payload */
	else
		cfpls = 0;	/* b000 - Max 8 bytes payload */

	cfg = (RCANFD_CFCC_CFTML(cftml) | RCANFD_CFCC_CFM(cfm) |
		RCANFD_CFCC_CFIM | RCANFD_CFCC_CFDC(cfdc) |
		RCANFD_CFCC_CFPLS(cfpls) | RCANFD_CFCC_CFTXIE);
	rcar_canfd_write(gpriv->base, RCANFD_CFCC(ch, RCANFD_CFFIFO_IDX), cfg);

	if (gpriv->fdmode)
		/* Clear FD mode specific control/status register */
		rcar_canfd_write(gpriv->base,
				 RCANFD_F_CFFDCSTS(ch, RCANFD_CFFIFO_IDX), 0);
}