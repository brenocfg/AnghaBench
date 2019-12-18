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
typedef  scalar_t__ u32 ;
struct decon_context {TYPE_1__* crtc; scalar_t__ addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  i80_mode; } ;

/* Variables and functions */
 scalar_t__ DECON_CRFMID ; 
 scalar_t__ DECON_VIDCON1 ; 
#define  VIDCON1_I80_ACTIVE 131 
#define  VIDCON1_VSTATUS_AC 130 
#define  VIDCON1_VSTATUS_BP 129 
 scalar_t__ VIDCON1_VSTATUS_MASK ; 
#define  VIDCON1_VSTATUS_VS 128 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 decon_get_frame_count(struct decon_context *ctx, bool end)
{
	u32 frm, pfrm, status, cnt = 2;

	/* To get consistent result repeat read until frame id is stable.
	 * Usually the loop will be executed once, in rare cases when the loop
	 * is executed at frame change time 2nd pass will be needed.
	 */
	frm = readl(ctx->addr + DECON_CRFMID);
	do {
		status = readl(ctx->addr + DECON_VIDCON1);
		pfrm = frm;
		frm = readl(ctx->addr + DECON_CRFMID);
	} while (frm != pfrm && --cnt);

	/* CRFMID is incremented on BPORCH in case of I80 and on VSYNC in case
	 * of RGB, it should be taken into account.
	 */
	if (!frm)
		return 0;

	switch (status & (VIDCON1_VSTATUS_MASK | VIDCON1_I80_ACTIVE)) {
	case VIDCON1_VSTATUS_VS:
		if (!(ctx->crtc->i80_mode))
			--frm;
		break;
	case VIDCON1_VSTATUS_BP:
		--frm;
		break;
	case VIDCON1_I80_ACTIVE:
	case VIDCON1_VSTATUS_AC:
		if (end)
			--frm;
		break;
	default:
		break;
	}

	return frm;
}