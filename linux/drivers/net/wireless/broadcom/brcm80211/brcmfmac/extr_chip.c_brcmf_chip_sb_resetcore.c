#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int base; } ;
struct brcmf_core_priv {TYPE_1__ pub; struct brcmf_chip_priv* chip; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  ctx; TYPE_2__* ops; } ;
struct TYPE_4__ {int (* read32 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write32 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_SB (int,int /*<<< orphan*/ ) ; 
 int SSB_IMSTATE_IBE ; 
 int SSB_IMSTATE_TO ; 
 int SSB_TMSHIGH_SERR ; 
 int SSB_TMSLOW_CLOCK ; 
 int SSB_TMSLOW_FGC ; 
 int SSB_TMSLOW_RESET ; 
 int /*<<< orphan*/  brcmf_chip_sb_coredisable (struct brcmf_core_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbimstate ; 
 int /*<<< orphan*/  sbtmstatehigh ; 
 int /*<<< orphan*/  sbtmstatelow ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void brcmf_chip_sb_resetcore(struct brcmf_core_priv *core, u32 prereset,
				    u32 reset, u32 postreset)
{
	struct brcmf_chip_priv *ci;
	u32 regdata;
	u32 base;

	ci = core->chip;
	base = core->pub.base;
	/*
	 * Must do the disable sequence first to work for
	 * arbitrary current core state.
	 */
	brcmf_chip_sb_coredisable(core, 0, 0);

	/*
	 * Now do the initialization sequence.
	 * set reset while enabling the clock and
	 * forcing them on throughout the core
	 */
	ci->ops->write32(ci->ctx, CORE_SB(base, sbtmstatelow),
			 SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK |
			 SSB_TMSLOW_RESET);
	regdata = ci->ops->read32(ci->ctx, CORE_SB(base, sbtmstatelow));
	udelay(1);

	/* clear any serror */
	regdata = ci->ops->read32(ci->ctx, CORE_SB(base, sbtmstatehigh));
	if (regdata & SSB_TMSHIGH_SERR)
		ci->ops->write32(ci->ctx, CORE_SB(base, sbtmstatehigh), 0);

	regdata = ci->ops->read32(ci->ctx, CORE_SB(base, sbimstate));
	if (regdata & (SSB_IMSTATE_IBE | SSB_IMSTATE_TO)) {
		regdata &= ~(SSB_IMSTATE_IBE | SSB_IMSTATE_TO);
		ci->ops->write32(ci->ctx, CORE_SB(base, sbimstate), regdata);
	}

	/* clear reset and allow it to propagate throughout the core */
	ci->ops->write32(ci->ctx, CORE_SB(base, sbtmstatelow),
			 SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK);
	regdata = ci->ops->read32(ci->ctx, CORE_SB(base, sbtmstatelow));
	udelay(1);

	/* leave clock enabled */
	ci->ops->write32(ci->ctx, CORE_SB(base, sbtmstatelow),
			 SSB_TMSLOW_CLOCK);
	regdata = ci->ops->read32(ci->ctx, CORE_SB(base, sbtmstatelow));
	udelay(1);
}