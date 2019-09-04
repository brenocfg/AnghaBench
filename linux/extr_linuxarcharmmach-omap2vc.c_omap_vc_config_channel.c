#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct voltagedomain {int /*<<< orphan*/  (* rmw ) (int,int,int /*<<< orphan*/ ) ;struct omap_vc_channel* vc; } ;
struct omap_vc_channel {int flags; int cfg_channel; int cfg_channel_sa_shift; int /*<<< orphan*/  cfg_channel_reg; } ;
struct TYPE_2__ {int racen; } ;

/* Variables and functions */
 int CFG_CHANNEL_MASK ; 
 int OMAP_VC_CHANNEL_DEFAULT ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* vc_cfg_bits ; 

__attribute__((used)) static int omap_vc_config_channel(struct voltagedomain *voltdm)
{
	struct omap_vc_channel *vc = voltdm->vc;

	/*
	 * For default channel, the only configurable bit is RACEN.
	 * All others must stay at zero (see function comment above.)
	 */
	if (vc->flags & OMAP_VC_CHANNEL_DEFAULT)
		vc->cfg_channel &= vc_cfg_bits->racen;

	voltdm->rmw(CFG_CHANNEL_MASK << vc->cfg_channel_sa_shift,
		    vc->cfg_channel << vc->cfg_channel_sa_shift,
		    vc->cfg_channel_reg);

	return 0;
}