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
struct rcar_canfd_channel {int channel; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCANFD_CCTR (int) ; 
 int RCANFD_CCTR_ALIE ; 
 int RCANFD_CCTR_BEIE ; 
 int RCANFD_CCTR_BLIE ; 
 int RCANFD_CCTR_BOEIE ; 
 int RCANFD_CCTR_BORIE ; 
 int RCANFD_CCTR_EPIE ; 
 int RCANFD_CCTR_EWIE ; 
 int RCANFD_CCTR_OLIE ; 
 int RCANFD_CCTR_TAIE ; 
 int /*<<< orphan*/  RCANFD_CERFL (int) ; 
 int /*<<< orphan*/  rcar_canfd_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcar_canfd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_canfd_disable_channel_interrupts(struct rcar_canfd_channel
						  *priv)
{
	u32 ctr, ch = priv->channel;

	ctr = (RCANFD_CCTR_TAIE |
	       RCANFD_CCTR_ALIE | RCANFD_CCTR_BLIE |
	       RCANFD_CCTR_OLIE | RCANFD_CCTR_BORIE |
	       RCANFD_CCTR_BOEIE | RCANFD_CCTR_EPIE |
	       RCANFD_CCTR_EWIE | RCANFD_CCTR_BEIE);
	rcar_canfd_clear_bit(priv->base, RCANFD_CCTR(ch), ctr);

	/* Clear any stray error flags */
	rcar_canfd_write(priv->base, RCANFD_CERFL(ch), 0);
}