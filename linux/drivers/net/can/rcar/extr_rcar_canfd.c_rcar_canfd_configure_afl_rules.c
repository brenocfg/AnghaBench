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
typedef  scalar_t__ u32 ;
struct rcar_canfd_global {int /*<<< orphan*/  base; scalar_t__ fdmode; } ;

/* Variables and functions */
 int RCANFD_CHANNEL_NUMRULES ; 
 int RCANFD_C_GAFL_OFFSET ; 
 int RCANFD_F_GAFL_OFFSET ; 
 int /*<<< orphan*/  RCANFD_GAFLCFG0 ; 
 int RCANFD_GAFLCFG_GETRNC (int /*<<< orphan*/ ,scalar_t__) ; 
 int RCANFD_GAFLCFG_SETRNC (scalar_t__,int) ; 
 int /*<<< orphan*/  RCANFD_GAFLECTR ; 
 int RCANFD_GAFLECTR_AFLDAE ; 
 int RCANFD_GAFLECTR_AFLPN (int) ; 
 int /*<<< orphan*/  RCANFD_GAFLID (int,int) ; 
 int /*<<< orphan*/  RCANFD_GAFLM (int,int) ; 
 int /*<<< orphan*/  RCANFD_GAFLP0 (int,int) ; 
 int /*<<< orphan*/  RCANFD_GAFLP1 (int,int) ; 
 int /*<<< orphan*/  RCANFD_GAFLP1_GAFLFDP (scalar_t__) ; 
 int RCANFD_GAFL_PAGENUM (int) ; 
 scalar_t__ RCANFD_RFFIFO_IDX ; 
 int /*<<< orphan*/  rcar_canfd_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rcar_canfd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_canfd_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcar_canfd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_canfd_configure_afl_rules(struct rcar_canfd_global *gpriv,
					   u32 ch)
{
	u32 cfg;
	int offset, start, page, num_rules = RCANFD_CHANNEL_NUMRULES;
	u32 ridx = ch + RCANFD_RFFIFO_IDX;

	if (ch == 0) {
		start = 0; /* Channel 0 always starts from 0th rule */
	} else {
		/* Get number of Channel 0 rules and adjust */
		cfg = rcar_canfd_read(gpriv->base, RCANFD_GAFLCFG0);
		start = RCANFD_GAFLCFG_GETRNC(0, cfg);
	}

	/* Enable write access to entry */
	page = RCANFD_GAFL_PAGENUM(start);
	rcar_canfd_set_bit(gpriv->base, RCANFD_GAFLECTR,
			   (RCANFD_GAFLECTR_AFLPN(page) |
			    RCANFD_GAFLECTR_AFLDAE));

	/* Write number of rules for channel */
	rcar_canfd_set_bit(gpriv->base, RCANFD_GAFLCFG0,
			   RCANFD_GAFLCFG_SETRNC(ch, num_rules));
	if (gpriv->fdmode)
		offset = RCANFD_F_GAFL_OFFSET;
	else
		offset = RCANFD_C_GAFL_OFFSET;

	/* Accept all IDs */
	rcar_canfd_write(gpriv->base, RCANFD_GAFLID(offset, start), 0);
	/* IDE or RTR is not considered for matching */
	rcar_canfd_write(gpriv->base, RCANFD_GAFLM(offset, start), 0);
	/* Any data length accepted */
	rcar_canfd_write(gpriv->base, RCANFD_GAFLP0(offset, start), 0);
	/* Place the msg in corresponding Rx FIFO entry */
	rcar_canfd_write(gpriv->base, RCANFD_GAFLP1(offset, start),
			 RCANFD_GAFLP1_GAFLFDP(ridx));

	/* Disable write access to page */
	rcar_canfd_clear_bit(gpriv->base,
			     RCANFD_GAFLECTR, RCANFD_GAFLECTR_AFLDAE);
}