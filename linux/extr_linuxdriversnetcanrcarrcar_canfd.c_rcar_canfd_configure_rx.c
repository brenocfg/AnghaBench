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
 int /*<<< orphan*/  RCANFD_RFCC (int) ; 
 int RCANFD_RFCC_RFDC (int) ; 
 int RCANFD_RFCC_RFIE ; 
 int RCANFD_RFCC_RFIM ; 
 int RCANFD_RFCC_RFPLS (int) ; 
 int RCANFD_RFFIFO_IDX ; 
 int /*<<< orphan*/  rcar_canfd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_canfd_configure_rx(struct rcar_canfd_global *gpriv, u32 ch)
{
	/* Rx FIFO is used for reception */
	u32 cfg;
	u16 rfdc, rfpls;

	/* Select Rx FIFO based on channel */
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	rfdc = 2;		/* b010 - 8 messages Rx FIFO depth */
	if (gpriv->fdmode)
		rfpls = 7;	/* b111 - Max 64 bytes payload */
	else
		rfpls = 0;	/* b000 - Max 8 bytes payload */

	cfg = (RCANFD_RFCC_RFIM | RCANFD_RFCC_RFDC(rfdc) |
		RCANFD_RFCC_RFPLS(rfpls) | RCANFD_RFCC_RFIE);
	rcar_canfd_write(gpriv->base, RCANFD_RFCC(ridx), cfg);
}