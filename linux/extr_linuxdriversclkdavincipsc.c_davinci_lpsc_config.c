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
struct davinci_lpsc_clk {int flags; int /*<<< orphan*/  md; int /*<<< orphan*/  regmap; int /*<<< orphan*/  pd; } ;
typedef  enum davinci_lpsc_state { ____Placeholder_davinci_lpsc_state } davinci_lpsc_state ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPCPR ; 
 int LPSC_FORCE ; 
 int /*<<< orphan*/  MDCTL (int /*<<< orphan*/ ) ; 
 int MDCTL_FORCE ; 
 int /*<<< orphan*/  MDSTAT (int /*<<< orphan*/ ) ; 
 int MDSTAT_STATE_MASK ; 
 int /*<<< orphan*/  PDCTL (int /*<<< orphan*/ ) ; 
 int PDCTL_EPCGOOD ; 
 int PDCTL_NEXT ; 
 int /*<<< orphan*/  PDSTAT (int /*<<< orphan*/ ) ; 
 int PDSTAT_STATE_MASK ; 
 int /*<<< orphan*/  PTCMD ; 
 int /*<<< orphan*/  PTSTAT ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void davinci_lpsc_config(struct davinci_lpsc_clk *lpsc,
				enum davinci_lpsc_state next_state)
{
	u32 epcpr, pdstat, mdstat, ptstat;

	regmap_write_bits(lpsc->regmap, MDCTL(lpsc->md), MDSTAT_STATE_MASK,
			  next_state);

	if (lpsc->flags & LPSC_FORCE)
		regmap_write_bits(lpsc->regmap, MDCTL(lpsc->md), MDCTL_FORCE,
				  MDCTL_FORCE);

	regmap_read(lpsc->regmap, PDSTAT(lpsc->pd), &pdstat);
	if ((pdstat & PDSTAT_STATE_MASK) == 0) {
		regmap_write_bits(lpsc->regmap, PDCTL(lpsc->pd), PDCTL_NEXT,
				  PDCTL_NEXT);

		regmap_write(lpsc->regmap, PTCMD, BIT(lpsc->pd));

		regmap_read_poll_timeout(lpsc->regmap, EPCPR, epcpr,
					 epcpr & BIT(lpsc->pd), 0, 0);

		regmap_write_bits(lpsc->regmap, PDCTL(lpsc->pd), PDCTL_EPCGOOD,
				  PDCTL_EPCGOOD);
	} else {
		regmap_write(lpsc->regmap, PTCMD, BIT(lpsc->pd));
	}

	regmap_read_poll_timeout(lpsc->regmap, PTSTAT, ptstat,
				 !(ptstat & BIT(lpsc->pd)), 0, 0);

	regmap_read_poll_timeout(lpsc->regmap, MDSTAT(lpsc->md), mdstat,
				 (mdstat & MDSTAT_STATE_MASK) == next_state,
				 0, 0);
}